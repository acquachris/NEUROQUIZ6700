#include "Arduino.h"
#include "structs/Hardware.h"
#include "Games/RFIDGame/RFIDGame.h"
#include "Buzzer.h"
#include "Music.h"
#include "Games/RFIDGame/RFIDGameData.h"

RFIDGame::RFIDGame(Hardware::Hardware& _hw) : hw(_hw){
    gameStatus = GameStatus::EXIT;
}

CardAssociation FindCardByCardId(const char* id){
    for(int i = 0; i < RFIDGameData::cardAssociationsLength; i++){
        if(strcmp(id, RFIDGameData::cardAssociations[i].cardId) == 0){
            return RFIDGameData::cardAssociations[i];
        }
    }

    return RFIDGameData::cardAssociations[RFIDGameData::cardAssociationsLength - 1];
}

CardAssociation FindCardByAnswerId(const char* answerId){
    for(int i = 0; i < RFIDGameData::cardAssociationsLength; i++){
        if(strcmp(answerId, RFIDGameData::cardAssociations[i].answerId) == 0){
            return RFIDGameData::cardAssociations[i];
        }
    }

    return RFIDGameData::cardAssociations[RFIDGameData::cardAssociationsLength - 1];
}

const char* RFIDGame::ReadCard() {
    static char uidStr[32];
    byte index = 0;
    static unsigned long lastDetectTime = 0;
    
    //Serial.println("Looking for card");

    if (millis() - lastDetectTime > 10000) {
        Serial.println("RFID timeout, reinitializing reader");
        hw.rfidSensor.PCD_Init();
        lastDetectTime = millis();
    }

    if (!hw.rfidSensor.PICC_IsNewCardPresent()) return nullptr;
    Serial.println("Card detected");

    if (!hw.rfidSensor.PICC_ReadCardSerial()) return nullptr;
    Serial.println("Card read");

    for (byte i = 0; i < hw.rfidSensor.uid.size; i++) {
        byte b = hw.rfidSensor.uid.uidByte[i];

        if (b < 0x10) uidStr[index++] = '0';
        index += sprintf(&uidStr[index], "%X", b);

        if (i < hw.rfidSensor.uid.size - 1)
            uidStr[index++] = ' ';
    }

    // Removal
    // Serial.println("Waiting for card removal...");
    // hw.lcd.WriteCentered("Rimuovi la scheda", "per continuare!");
    // while (hw.rfidSensor.PICC_IsNewCardPresent()) {
    //     delay(50);
    // }

    uidStr[index] = '\0';

    hw.rfidSensor.PICC_HaltA();
    hw.rfidSensor.PCD_StopCrypto1();

    return uidStr;
}

void RFIDGame::Init(){
    gameStatus = GameStatus::INTRO;
    wrongAnswers = 0;
    correctAnswers = 0;
    lastQuestionNumber = -1;
    currentQuestionNumber = 0;
    hw.rgbLedRfid.Off();

    hw.lcd.WriteCentered("Gioco selezionato:", "Associa la Carta");

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::RFIDMusic;
    options.size = 6;

    hw.buzzer.Play(options);
    
    delay(5000);

    options.notes = Music::Beep;
    options.size = 1;

    hw.buzzer.Play(options);

    hw.lcd.SafeWrite("Associa i compiti e le caratteristiche del Sistema Nervoso ad una carta.");

    delay(5000);

    gameStatus = GameStatus::QUESTION;
}

void RFIDGame::PromptQuestion(int number){
    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    gameStatus = GameStatus::QUESTION;

    RFIDQuestion question = RFIDGameData::questions[number];

    hw.rgbLedRfid.SetColor(255, 255, 255);

    // Calculate required length
    int needed = snprintf(nullptr, 0, "%d) %s", number + 1, question.text) + 1;

    char* fullText = (char*)malloc(needed);
    if(fullText == nullptr){
        return;
    }

    snprintf(fullText, needed, "%d) %s", number + 1, question.text);

    int pageCount = 0;
    char** pages = hw.lcd.CreatePagesFromText(fullText, &pageCount);

    hw.lcd.SetPages(pages, pageCount);
    hw.buzzer.Play(options);

    currentQuestionNumber = number;

    free(fullText);
}

void RFIDGame::HandleArrowButtons() {
    if(gameStatus != GameStatus::QUESTION) return;

    // Check debounce
    if(millis() - lastPressTime < 500) return;

    bool isRightPressed = hw.buttonRight.GetState();
    bool isLeftPressed = hw.buttonLeft.GetState();

    if(!isRightPressed && !isLeftPressed) return;

    // Update debounce time
    lastPressTime = millis();

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    hw.lcd.MovePage(isRightPressed);

    hw.buzzer.Play(options);
}

void RFIDGame::ShowResults() {
    gameStatus = GameStatus::RESULT;

    hw.rgbLedRfid.Off();

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    char line[21];

    // Risposte Corrette
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte giuste: %d",
        correctAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // Risposte sbagliate
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte errate: %d",
        wrongAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // Risultato finale
    int totalAnswers = correctAnswers + wrongAnswers;

    int grade = (totalAnswers > 0)
        ? floor(correctAnswers * 10 / totalAnswers)
        : 0.0f;

    if(grade >= 6){
        hw.rgbLedRfid.SetColor(0, 255, 0);
    }else{
        hw.rgbLedRfid.SetColor(255, 0, 0);
    }

    options.size = 4;
    options.notes = (grade >= 6)
        ? Music::CorrectMusic
        : Music::WrongMusic;

    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "%d/%d (Voto: %d/10)",
        correctAnswers,
        totalAnswers,
        grade
    );

    hw.lcd.WriteCentered("Risultato finale:", line);
}

void RFIDGame::CheckForQuestionChange(){
    if(currentQuestionNumber == lastQuestionNumber) return;

    lastQuestionNumber = currentQuestionNumber;

    if(currentQuestionNumber >= RFIDGameData::questionsLength){
        ShowResults();
        return;
    }

    PromptQuestion(currentQuestionNumber);
}

void RFIDGame::ShowAnswer(bool wasCorrect){
    gameStatus = GameStatus::ANSWER;

    Buzzer::BuzzerPlayOptions options;
    options.notes = wasCorrect ? Music::CorrectMusic : Music::WrongMusic;
    options.size = 4;
    options.lastNoteMultiplier = 4;


    RFIDQuestion question = RFIDGameData::questions[currentQuestionNumber];

    if(wasCorrect){
        hw.lcd.WriteCentered("Esatto! Complimenti!", "Risposta esatta!");
        hw.rgbLedRfid.SetColor(0, 255, 0);
        hw.buzzer.Play(options);

        delay(3000);
    }else{
        hw.rgbLedRfid.SetColor(255, 0, 0);
        hw.lcd.WriteCentered("No! Hai sbagliato!", "Risposta errata!");
        hw.buzzer.Play(options);

        delay(3000);

        options.notes = Music::Beep;
        options.size = 1;
        options.lastNoteMultiplier = 1;

        CardAssociation cardAssociation = FindCardByAnswerId(question.answerId);
        hw.lcd.WriteCentered("Risposta esatta:", cardAssociation.readableAnswer);
        
        hw.buzzer.Play(options);

        delay(5000);
    }

    currentQuestionNumber++;
}

void RFIDGame::CheckForAnswer(){
    const char* cardId = ReadCard();

    if(cardId == nullptr) return;

    RFIDQuestion currentQuestion = RFIDGameData::questions[currentQuestionNumber];
    CardAssociation cardAssociation = FindCardByCardId(cardId);

    bool isCorrect = true;
    if(strcmp(currentQuestion.answerId, cardAssociation.answerId) == 0){
        // Answer is correct
        correctAnswers++;
    }else{
        // Answer is wrong
        wrongAnswers++;
        isCorrect = false;
    }

    ShowAnswer(isCorrect);
}

void RFIDGame::Tick(){
    if(gameStatus != GameStatus::QUESTION && gameStatus != GameStatus::ANSWER) return;

    CheckForAnswer();
    CheckForQuestionChange();
    HandleArrowButtons();
}

void RFIDGame::Exit(){
    gameStatus = GameStatus::EXIT;
    wrongAnswers = 0;
    correctAnswers = 0;
    lastQuestionNumber = -1;
    currentQuestionNumber = 0;
    hw.rgbLedRfid.Off();
}