#include <Arduino.h>
#include "Lcd.h"
#include "Led.h"
#include "Buzzer.h"
#include "RGBLed.h"
#include "ThreePositionSwitch.h"
#include "Pins.h"
#include "Music.h"
#include "Keypad.h"
#include "SPI.h"
#include "MFRC522.h"
#include "Button.h"

#include "Wire.h"

#include "structs\Hardware.h"
#include "enums/GameState.h"

#include "Games/Menu/Menu.h"
#include "Games/RFIDGame/RFIDGame.h"
#include "Games/KeypadGame/KeypadGame.h"
#include "Games/QuestionGame/QuestionGame.h"

// Instantiate all components

Lcd lcd;

Buzzer buzzer(Pins::BUZZER);

Led ledGreenA(Pins::LED_GREEN_A);
Led ledRedA(Pins::LED_RED_A);

Led ledGreenB(Pins::LED_GREEN_B);
Led ledRedB(Pins::LED_RED_B);

Led ledGreenC(Pins::LED_GREEN_C);
Led ledRedC(Pins::LED_RED_C);

Led ledGreenD(Pins::LED_GREEN_D);
Led ledRedD(Pins::LED_RED_D);

RGBLed rgbLedKeypad(Pins::LED_KEYPAD_RED, Pins::LED_KEYPAD_GREEN, Pins::LED_KEYPAD_BLUE);
RGBLed rgbLedRfid(Pins::LED_RFID_RED, Pins::LED_RFID_GREEN, Pins::LED_RFID_BLUE);

Button buttonAAnswer(Pins::BUTTON_A);
Button buttonBAnswer(Pins::BUTTON_B);
Button buttonCAnswer(Pins::BUTTON_C);
Button buttonDAnswer(Pins::BUTTON_D);
Button buttonLeft(Pins::BUTTON_LEFT);
Button buttonRight(Pins::BUTTON_RIGHT);

ThreePositionSwitch menuSwitch(Pins::THREE_POSITION_SWITCH_LEFT, Pins::THREE_POSITION_SWITCH_RIGHT);

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[KEYPAD_ROWS] = { Pins::KEYPAD_8, Pins::KEYPAD_7, Pins::KEYPAD_6, Pins::KEYPAD_5 };
byte colPins[KEYPAD_COLS] = { Pins::KEYPAD_4, Pins::KEYPAD_3, Pins::KEYPAD_2, Pins::KEYPAD_1 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

MFRC522 rfidSensor(Pins::RFID_SDA, Pins::RFID_RESET);

// Create the Hardware struct

Hardware::Hardware hw {
    lcd,
    buzzer,
    keypad,
    menuSwitch,

    buttonAAnswer,
    buttonBAnswer,
    buttonCAnswer,
    buttonDAnswer,
    buttonLeft,
    buttonRight,

    ledGreenA,
    ledRedA,
    ledGreenB,
    ledRedB,
    ledGreenC,
    ledRedC,
    ledGreenD,
    ledRedD,

    rgbLedKeypad,
    rgbLedRfid,

    rfidSensor
};

GameState::GameState gameState = GameState::INTRO;
GameState::GameState previousGameState = GameState::INTRO;

// Game Modes
Menu menuScreen(hw);
RFIDGame rfidGame(hw);
KeypadGame keypadGame(hw);
QuestionGame questionGame(hw);

void setup() {
    // ### INIT ###
    Serial.begin(9600);
    lcd.Init();

    keypad.setHoldTime(1000);

    Wire.setClock(10000);
    SPI.begin();
    rfidSensor.PCD_Init();

    // ### Starting Sequence ###
    
    // Write welcome message
    lcd.WriteCentered("Benvenuto in", "NEUROQUIZ-6700");

    // Play tone
    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::CorrectMusic;
    options.size = 4;
    options.lastNoteMultiplier = 8;

    buzzer.Play(options);

    delay(5000);

    gameState = GameState::MENU;
}

void ExitLastGame(){
    switch(previousGameState){
        case GameState::MENU:
            menuScreen.Exit();
            break;

        case GameState::KEYPAD_GAME:
            keypadGame.Exit();
            break;

        case GameState::RFID_GAME:
            rfidGame.Exit();
            break;

        case GameState::QUESTION_GAME:
            questionGame.Exit();
            break;
        default:
            break;
    }
}

void HandleGameStateChange() {
    ExitLastGame();

    previousGameState = gameState;

    switch (gameState)
    {
        case GameState::INTRO:
            break;
        case GameState::MENU:
            menuScreen.Init();

            break;
        case GameState::QUESTION_GAME:
            Serial.println("Initializing question game");
            questionGame.Init();
            break;
        case GameState::KEYPAD_GAME:
            Serial.println("Initializing keypad game");
            keypadGame.Init();
            break;
        case GameState::RFID_GAME:
            Serial.println("Initializing RFID game");
            rfidGame.Init();
            break;
        default:
            break;
    }
}

const GameState::GameState GetStateFromPosition(ThreePositionSwitch::Position position){
    // 27/05/2026, visto che lo switch si è rotto si passa all'uso di pulsanti.
    // Mi scuso per l'implementazione ignorante. Domani devo partire per Londra, non ho tempo ;-;

    int currentMenuIndex = menuScreen.GetCurrentMenuIndex();
   
    // switch (position){
    //     case ThreePositionSwitch::LEFT:
    //         return GameState::KEYPAD_GAME;
    //         break;

    //     case ThreePositionSwitch::CENTER:
    //         return GameState::QUESTION_GAME;
    //         break;

    //     case ThreePositionSwitch::RIGHT:
    //         return GameState::RFID_GAME;
    //         break;

    //     default:
    //         return GameState::QUESTION_GAME;
    //         break;
    // }

    switch(currentMenuIndex){
        case 0:
            return GameState::KEYPAD_GAME;
            break;

        case 1:
            return GameState::QUESTION_GAME;
            break;

        case 2:
            return GameState::RFID_GAME;
            break;

        default:
            return GameState::QUESTION_GAME;
            break;
    }
}

// Cari ragazzi, un piccolo mio marchio lo devo lasciare
// Premendo C nel menù escoo i crediti. Siamo onesti qui...
void ShowCredits(){
    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::CorrectMusic;
    options.size = 4;
    options.lastNoteMultiplier = 8;

    lcd.SafeWrite("Elettronica & Programmazione: Acquarola Christian 4CLS A.S. 2025/2026");

    buzzer.Play(options);
}

void loop() {
    if(gameState != previousGameState){
        HandleGameStateChange();
    }

    if(gameState == GameState::MENU && buttonCAnswer.GetState()){
        ShowCredits();
    }

    // Update each state
    switch(gameState){
        case GameState::MENU:
            menuScreen.Tick();
            break;

        case GameState::QUESTION_GAME:
            questionGame.Tick();
            break;

        case GameState::KEYPAD_GAME:
            keypadGame.Tick();
            break;

        case GameState::RFID_GAME:
            rfidGame.Tick();
            break;
        default:
            break;
    }


    if(gameState != GameState::INTRO){ 
        keypad.getKeys();
        for (int i = 0; i < LIST_MAX; i++) { 
            if(keypad.key[i].kstate == HOLD && keypad.key[i].kchar == 'B'){
                keypad.key[i].kstate = IDLE;

                if(gameState != GameState::MENU){
                    gameState = GameState::MENU;
                }else{
                    gameState = GetStateFromPosition(hw.menuSwitch.GetReading());
                }
            }
        }
    }
}

// Sabato 07/02/2026, ore 21:12
// La logica principale del gioco è conclusa. Funziona tutto.
// Questo progetto mi ha fatto venire diversi mal di testa
// Si ringrazia il Ketoprofone (oki) per avermi aiutato
// È stata una lunga, lunga, lunga avventura. Uno speciale ringraziamento e saluto al carissimo Prof. Tinari per i consigli.
// ~ Christian