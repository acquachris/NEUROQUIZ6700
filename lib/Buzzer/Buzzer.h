#pragma once

#include "Arduino.h"

class Buzzer {
    private:
        int _pin;

    public:
        struct BuzzerPlayOptions {
            const int* notes;
            int size;
            int noteDuration = 100;
            int delayMs = 0;
            int lastNoteMultiplier = 1;
            bool ignoreDelay = false;
        };
        
        Buzzer(int pin);

        void Play(BuzzerPlayOptions options);
};