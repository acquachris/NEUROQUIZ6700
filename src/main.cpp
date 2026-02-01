#include <Arduino.h>
#include "Lcd.h"
#include "Led.h"
#include "Buzzer.h"
#include "RGBLed.h"
#include "ThreePositionSwitch.h"
#include "Pins.h"
#include "Music.h"
#include "Keypad.h"

#include "structs\Hardware.h"
#include "enums/GameState.h"

#include "Games/Menu/Menu.h"

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

// Create the Hardware struct

Hardware::Hardware hw {
    lcd,
    buzzer,
    keypad,
    menuSwitch,

    ledGreenA,
    ledRedA,
    ledGreenB,
    ledRedB,
    ledGreenC,
    ledRedC,
    ledGreenD,
    ledRedD,

    rgbLedKeypad,
    rgbLedRfid
};

GameState::GameState gameState = GameState::INTRO;
GameState::GameState previousGameState = GameState::INTRO;

// Game Modes
Menu menuScreen(hw);

void setup() {
    // ### INIT ###
    Serial.begin(9600);
    lcd.Init();

    keypad.setHoldTime(1000);

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
        break;
    case GameState::KEYPAD_GAME:
        Serial.println("Initializing keypad game");
        break;
    case GameState::RFID_GAME:
        Serial.println("Initializing RFID game");
        break;
    default:
        break;
    }
}

const GameState::GameState GetStateFromPosition(ThreePositionSwitch::Position position){
    switch (position){
        case ThreePositionSwitch::LEFT:
            return GameState::KEYPAD_GAME;
            break;

        case ThreePositionSwitch::CENTER:
            return GameState::QUESTION_GAME;
            break;

        case ThreePositionSwitch::RIGHT:
            return GameState::RFID_GAME;
            break;

        default:
            return GameState::QUESTION_GAME;
            break;
    }
}

void loop() {
    if(gameState != previousGameState){
        HandleGameStateChange();
    }

    // Update each state
    switch(gameState){
        case GameState::MENU:
            menuScreen.Tick();
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