#pragma once

#include "Lcd.h"
#include "Led.h"
#include "Buzzer.h"
#include "RGBLed.h"
#include "ThreePositionSwitch.h"
#include "Keypad.h"
#include "MFRC522.h"
#include "Button.h"

namespace Hardware {
    struct Hardware {
        Lcd& lcd;
        Buzzer& buzzer;
        Keypad& keypad;
        ThreePositionSwitch& menuSwitch;

        Button& buttonAAnswer;
        Button& buttonBAnswer;
        Button& buttonCAnswer;
        Button& buttonDAnswer;
        Button& buttonLeft;
        Button& buttonRight;

        Led& ledGreenA;
        Led& ledRedA;
        Led& ledGreenB;
        Led& ledRedB;
        Led& ledGreenC;
        Led& ledRedC;
        Led& ledGreenD;
        Led& ledRedD;

        RGBLed& rgbLedKeypad;
        RGBLed& rgbLedRfid;

        MFRC522 rfidSensor;
    };
}