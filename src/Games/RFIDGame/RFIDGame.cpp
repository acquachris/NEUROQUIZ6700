#include "Arduino.h"
#include "structs/Hardware.h"
#include "Games/RFIDGame/RFIDGame.h"
#include "Buzzer.h"
#include "Music.h"
#include "Games/RFIDGame/RFIDGameData.h"

RFIDGame::RFIDGame(Hardware::Hardware& _hw) : hw(_hw){
    gameStatus = GameStatus::INTRO;
}

const char* RFIDGame::ReadCard() {
    static char uidStr[32];
    byte index = 0;

    if (!hw.rfidSensor.PICC_IsNewCardPresent()) return nullptr;
    if (!hw.rfidSensor.PICC_ReadCardSerial()) return nullptr;

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

    hw.lcd.SafeWrite(question.text);
    hw.buzzer.Play(options);

    currentQuestionNumber = number;
}

void RFIDGame::ShowResults() {
    gameStatus = GameStatus::RESULT;

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    char line[21]; // 20 chars + '\0'

    // --- Risposte corrette ---
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte esatte: %d",
        correctAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // --- Risposte errate ---
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte errate: %d",
        wrongAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // --- Risultato finale ---
    int totalAnswers = correctAnswers + wrongAnswers;

    // Evita divisione per zero (VERY important)
    int grade = (totalAnswers > 0)
        ? round((correctAnswers * 10.0f) / totalAnswers)
        : 0;

    options.size = 4;
    options.notes = (grade >= 6)
        ? Music::CorrectMusic
        : Music::WrongMusic;

    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "%d/%d (Voto: %d)",
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

        delay(3000);
    }else{
        hw.lcd.WriteCentered("Sbagliato!", "Risposta sbagliata!");
        hw.buzzer.Play(options);

        delay(3000);

        // TODO: Show readable result instead of card id
        hw.lcd.WriteCentered("Risposta esatta:", question.cardId);
        
        delay(5000);
    }

    currentQuestionNumber++;
}

void RFIDGame::CheckForAnswer(){
    const char* cardId = ReadCard();

    if(cardId == nullptr) return;

    Question currentQuestion = RFIDGameData::questions[currentQuestionNumber];

    bool isCorrect = true;
    if(strcmp(cardId, currentQuestion.cardId) == 0){
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
}