#pragma once

#include "Lcd.h"
#include "Led.h"
#include "Buzzer.h"
#include "RGBLed.h"
#include "ThreePositionSwitch.h"
#include "Keypad.h"

namespace Hardware {
    struct Hardware {
        Lcd& lcd;
        Buzzer& buzzer;
        Keypad& keypad;
        ThreePositionSwitch& menuSwitch;

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
    };
}