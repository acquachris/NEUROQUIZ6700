#include "Arduino.h"
#include "Menu.h"
#include "structs\Hardware.h"
#include "Music.h"
#include "enums\GameState.h"
#include "Games/Menu/MenuData.h"

const char* GetGameNameFromPosition(ThreePositionSwitch::Position position){
    switch (position){
        case ThreePositionSwitch::LEFT:
            return "Cruciverba";
            break;

        case ThreePositionSwitch::CENTER:
            return "Quiz";
            break;

        case ThreePositionSwitch::RIGHT:
            return "Associa la Carta";
            break;

        default:
            return "non puoi essere qui!";
            break;
    }
}

const char* GetGameNameFromIndex(int index){
    switch (index){
        case 0:
            return "Cruciverba";
            break;

        case 1:
            return "Quiz";
            break;

        case 2:
            return "Associa la Carta";
            break;

        default:
            return "non puoi essere qui!";
            break;
    }
}

Menu::Menu(Hardware::Hardware& _hw) : hw(_hw){}

void Menu::Init(){
    currentNote = -1;

    currentMenuIndex = 0;
    menuLoaded = false;
}

void Menu::Exit(){
    Serial.println("Exiting menu screen");
    currentNote = -1;
    
    hw.rgbLedKeypad.Off();
    hw.rgbLedRfid.Off();

    hw.ledGreenA.Off();
    hw.ledGreenB.Off();
    hw.ledGreenC.Off();
    hw.ledGreenD.Off();

    hw.lcd.Clear();

    hw.menuSwitch.Reset();
}

void Menu::Tick(){
    Lcd& lcd = hw.lcd;

    // ! 27/05/2026, Lo switch si è rotto in fase di scrittura del capolavoro. Si cambia il sistema quindi con i pulsanti.

    // ThreePositionSwitch::Position currentPosition = hw.menuSwitch.GetPosition();

    // if(currentPosition == ThreePositionSwitch::UNCHANGED){
    //     return;
    // }

    // const char* gameName = GetGameNameFromPosition(currentPosition);

    const bool isRightPressed = hw.buttonRight.GetState();
    const bool isLeftPressed = hw.buttonLeft.GetState();
    
    if(menuLoaded && (!isRightPressed && !isLeftPressed)) return;

    menuLoaded = true;

    if(isRightPressed){
        currentMenuIndex++;
    }else if(isLeftPressed){
        currentMenuIndex--;
    }

    if(currentMenuIndex < 0){
        currentMenuIndex = 2;
    }else if(currentMenuIndex >= MenuData::numberOfGames){
        currentMenuIndex = 0;
    }

    const char* gameName = GetGameNameFromIndex(currentMenuIndex);

    // switch(currentPosition){
    //     case ThreePositionSwitch::LEFT:
    //         hw.rgbLedKeypad.SetColor(0, 0, 255);

    //         hw.rgbLedRfid.Off();

    //         hw.ledGreenA.Off();
    //         hw.ledGreenB.Off();
    //         hw.ledGreenC.Off();
    //         hw.ledGreenD.Off();
    //         break;

    //     case ThreePositionSwitch::CENTER:
    //         hw.rgbLedKeypad.Off();
    //         hw.rgbLedRfid.Off();

    //         hw.ledGreenA.On();
    //         hw.ledGreenB.On();
    //         hw.ledGreenC.On();
    //         hw.ledGreenD.On();

    //         break;

    //     case ThreePositionSwitch::RIGHT:
    //         hw.rgbLedKeypad.Off();
    //         hw.rgbLedRfid.SetColor(255, 255, 0);

    //         hw.ledGreenA.Off();
    //         hw.ledGreenB.Off();
    //         hw.ledGreenC.Off();
    //         hw.ledGreenD.Off();

    //         break;

    //     case ThreePositionSwitch::UNCHANGED:
    //     default: 
    //         break;
    // }

    switch(currentMenuIndex){
        case 0:
            hw.rgbLedKeypad.SetColor(0, 0, 255);

            hw.rgbLedRfid.Off();

            hw.ledGreenA.Off();
            hw.ledGreenB.Off();
            hw.ledGreenC.Off();
            hw.ledGreenD.Off();
            break;

        case 1:
            hw.rgbLedKeypad.Off();
            hw.rgbLedRfid.Off();

            hw.ledGreenA.On();
            hw.ledGreenB.On();
            hw.ledGreenC.On();
            hw.ledGreenD.On();

            break;

        case 2:
            hw.rgbLedKeypad.Off();
            hw.rgbLedRfid.SetColor(255, 255, 0);

            hw.ledGreenA.Off();
            hw.ledGreenB.Off();
            hw.ledGreenC.Off();
            hw.ledGreenD.Off();

            break;

        default: 
            break;
    }
    
    // Troviamo le note!
    Buzzer::BuzzerPlayOptions options;

    // options.notes = Music::Beep; NAH IL BEEP È NOIOSO, MEGLIO YLIA.
    
    if(currentNote >= MenuData::numberOfNotes){
        currentNote = 0;
    }

    int notes[1];
    notes[0] = currentNote >= 0 ? MenuData::menuMusic[currentNote] : Music::Beep[0];
    currentNote++;

    options.notes = notes;
    options.size = 1;
    options.ignoreDelay = true;
    options.noteDuration = 150;

    lcd.WriteCentered("Seleziona gioco:", gameName);

    hw.buzzer.Play(options);
}

int Menu::GetCurrentMenuIndex(){
    return currentMenuIndex;
}