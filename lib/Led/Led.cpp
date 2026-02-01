#include <Arduino.h>
#include <Led.h>

Led::Led(int pin){
    _pin = pin;
    _state = false;
    pinMode(_pin, OUTPUT);
}

Led::Led(int pin, bool state){
    _pin = pin;
    pinMode(_pin, OUTPUT);

    SetState(state);
}

bool Led::GetState(){
    return _state;
}

void Led::On(){
    digitalWrite(_pin, HIGH);
    _state = true;
}

void Led::Off(){
    digitalWrite(_pin, LOW);
    _state = false;
}

void Led::SetState(bool state){
    _state = state;
    digitalWrite(_pin, _state ? HIGH : LOW);
}