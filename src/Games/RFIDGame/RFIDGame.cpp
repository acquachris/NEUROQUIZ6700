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
    
    Serial.println("Looking for card");
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

    uidStr[index] = '\0';

    hw.rfidSensor.PICC_HaltA();

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

    hw.lcd.SafeWrite("Associa i compiti del Sistema Nervoso ad una carta.");

    delay(5000);

    gameStatus = GameStatus::QUESTION;
}

void RFIDGame::PromptQuestion(int number){
    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;


    Question question = RFIDGameData::questions[number];

    hw.rgbLedRfid.SetColor(255, 255, 255);

    char line[84];

    snprintf(
        line,
        sizeof(line),
        "%d) %s",
        number + 1, 
        question.text
    );

    hw.lcd.SafeWrite(line);
    hw.buzzer.Play(options);

    currentQuestionNumber = number;
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

    if(grade > 6){
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


    Question question = RFIDGameData::questions[currentQuestionNumber];

    if(wasCorrect){
        hw.lcd.WriteCentered("Esatto! Complimenti!", "Risposta esatta!");
        hw.buzzer.Play(options);
        hw.rgbLedRfid.SetColor(0, 255, 0);

        delay(3000);
    }else{
        hw.rgbLedRfid.SetColor(255, 0, 0);
        hw.lcd.WriteCentered("No! Hai sbagliato!", "Risposta errata!");
        hw.buzzer.Play(options);

        delay(3000);

        CardAssociation cardAssociation = FindCardByAnswerId(question.answerId);
        hw.lcd.WriteCentered("Risposta esatta:", cardAssociation.readableAnswer);
        
        delay(5000);
    }

    currentQuestionNumber++;
}

void RFIDGame::CheckForAnswer(){
    const char* cardId = ReadCard();

    if(cardId == nullptr) return;

    Question currentQuestion = RFIDGameData::questions[currentQuestionNumber];
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
}

void RFIDGame::Exit(){
    gameStatus = GameStatus::EXIT;
    wrongAnswers = 0;
    correctAnswers = 0;
    lastQuestionNumber = -1;
    currentQuestionNumber = 0;
    hw.rgbLedRfid.Off();
}