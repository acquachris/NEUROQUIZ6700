#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer(int pin){
    _pin = pin;

    pinMode(_pin, OUTPUT);
}

void Buzzer::Play(BuzzerPlayOptions options){
    for(int i = 0; i < options.size; i++){
        int multiplier = i + 1 == options.size ? options.lastNoteMultiplier : 1;

        tone(_pin, options.notes[i], options.noteDuration * multiplier);
        
        if(!options.ignoreDelay){
            delay(options.delayMs + options.noteDuration);
        }
    }
}