#include "Games/KeypadGame/KeypadGame.h"
#include "Games/KeypadGame/KeypadGameData.h"

#include "Music.h"

KeypadGame::KeypadGame(Hardware::Hardware& _hw) : hw(_hw){
    gameStatus = GameStatus::EXIT;
}

void KeypadGame::ClearAnswerFromMemory(){
    for(int i = 0; i < sizeof(answer); i++){
        answer[i] = '\0';
    }
}

void KeypadGame::Init(){
    ClearAnswerFromMemory();
    numberOfTries = 1;

    gameStatus = GameStatus::INTRO;

    hw.lcd.WriteCentered("Gioco selezionato:", "Cruciverba");

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::KeypadMusic;
    options.size = 6;

    hw.buzzer.Play(options);
    
    delay(5000);

    options.notes = Music::Beep;
    options.size = 1;

    hw.buzzer.Play(options);

    hw.lcd.SafeWrite("Risolvi il cruciverba e scrivi il codice!");

    delay(5000);

    hw.buzzer.Play(options);

    hw.lcd.Clear();
    hw.lcd.WriteLine("Istruzioni tastiera:", 0);
    hw.lcd.WriteLine("A: Cancella ultimo", 1);
    hw.lcd.WriteLine("C: Resetta risposta", 2);
    hw.lcd.WriteLine("D: Invia risposta", 3);

    delay(5000);

    gameStatus = GameStatus::INSERTING;
    
    hw.rgbLedKeypad.SetColor(255, 255, 255);
    UpdateLcd();
}

void KeypadGame::CheckAnswer(){
    gameStatus = GameStatus::ANSWER;

    if(strcmp(answer, KeypadGameData::correctAnswer) == 0){
        hw.rgbLedKeypad.SetColor(0, 255, 0);
        hw.lcd.WriteCentered("Esatto! Complimenti!", "Risposta esatta!");
        Buzzer::BuzzerPlayOptions options;
        options.notes = Music::CorrectMusic;
        options.size = 4;
        options.lastNoteMultiplier = 4;

        hw.buzzer.Play(options);

        delay(5000);

        options.notes = Music::Beep;
        options.size = 1;

        char line[21];

        snprintf(
            line,
            sizeof(line),
            "Numero di Tentativi: %d",
            numberOfTries
        );

        hw.lcd.WriteCentered("Esatto! Complimenti!", line);

        return;
    }else{
        hw.rgbLedKeypad.SetColor(255, 0, 0);
        hw.lcd.WriteCentered("No! Hai sbagliato!", "Risposta errata!");

        Buzzer::BuzzerPlayOptions options;
        options.notes = Music::WrongMusic;
        options.size = 4;

        hw.buzzer.Play(options);

        delay(5000);

        gameStatus = GameStatus::AWAITING_RETRY;
        
        options.notes = Music::Beep;
        options.size = 1;

        hw.lcd.WriteCentered("Vuoi riprovare?", "A: Si          B: No");

        hw.rgbLedKeypad.Off();
        hw.ledGreenA.On();
        hw.ledRedB.On();

        hw.buzzer.Play(options);
    }
}

void KeypadGame::CheckKeypad(){
    char key = hw.keypad.getKey();
    if (!key) return;

    switch (key){
        case 'A': {
            int len = strlen(answer);
            if (len > 0){
                answer[len - 1] = '\0';
                UpdateLcd();
            }
            break;
        }

        case 'C': {
            ClearAnswerFromMemory();
            UpdateLcd();
            break;
        }

        case 'D': {
            if(strlen(answer) == KeypadGameData::answerLength){
                CheckAnswer();
            }
            break;
        }

        default: {
            if(key == 'B' || key == '*'|| key == '#') break;

            int len = strlen(answer);
            if (len < sizeof(answer) - 1){
                answer[len] = key;
                answer[len + 1] = '\0';
                UpdateLcd();
            }
            break;
        }
    }
}

void KeypadGame::UpdateLcd(){
    hw.lcd.Clear();

    char display[16];
    for (int i = 0; i < 15; i++){
        if (answer[i] != '\0'){
            display[i] = answer[i];
        } else {
            display[i] = '_';
        }
    }
    display[15] = '\0';

    hw.lcd.WriteCentered("Inserisci il codice:", display);

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    hw.buzzer.Play(options);
}

void KeypadGame::CheckForRetry(){
    if(gameStatus != GameStatus::AWAITING_RETRY) return;

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    if(hw.buttonAAnswer.GetState()){
        gameStatus = GameStatus::INSERTING;
        ClearAnswerFromMemory();

        hw.ledGreenA.Off();
        hw.ledRedB.Off();

        numberOfTries++;

        char line[21];

        snprintf(
            line,
            sizeof(line),
            "Tentativo N. %d",
            numberOfTries
        );

        hw.lcd.WriteCentered("Riprova!", line);

        hw.buzzer.Play(options);

        delay(5000);

        hw.rgbLedKeypad.SetColor(255, 255, 255);
        UpdateLcd();
        return;
    }

    if(!hw.buttonBAnswer.GetState()) return;

    hw.ledGreenA.Off();
    hw.ledRedB.Off();

    char line[21];
    snprintf(
        line,
        sizeof(line),
        "%s",
        KeypadGameData::correctAnswer
    );

    gameStatus = GameStatus::ANSWER;

    options.notes = Music::WrongMusic;
    options.size = 4;

    hw.rgbLedKeypad.SetColor(255, 0, 0);

    hw.lcd.WriteCentered("Hai perso!", "Ti sei arreso.");

    hw.buzzer.Play(options);

    delay(5000);

    options.notes = Music::Beep;
    options.size = 1;

    hw.lcd.WriteCentered("Risposta corretta:", line);
    hw.buzzer.Play(options);
}

void KeypadGame::Tick(){
    if(gameStatus == GameStatus::AWAITING_RETRY){
        CheckForRetry();
        return;
    }

    if(gameStatus != GameStatus::INSERTING) return;

    CheckKeypad();
}

void KeypadGame::Exit(){
    gameStatus = GameStatus::EXIT;
    hw.ledGreenA.Off();
    hw.ledRedB.Off();
    hw.rgbLedKeypad.Off();
    ClearAnswerFromMemory();
    numberOfTries = 1;
}