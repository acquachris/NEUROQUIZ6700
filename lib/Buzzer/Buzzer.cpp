#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer(int pin){
    _pin = pin;

    pinMode(_pin, OUTPUT);
}

void Buzzer::Play(BuzzerPlayOptions options){
    // Ignore delay for beep (1 note only)
    bool shouldIgnoreDelay = options.ignoreDelay;

    if(options.size == 1){
        shouldIgnoreDelay = true;
    }

    for(int i = 0; i < options.size; i++){
        int multiplier = i + 1 == options.size ? options.lastNoteMultiplier : 1;

        tone(_pin, options.notes[i], options.noteDuration * multiplier);
        
        if(!shouldIgnoreDelay){
            delay(options.delayMs + options.noteDuration);
        }
    }
}