#include "Arduino.h"
#include "Button.h"

Button::Button(int pin){
    _pin = pin;
    _lastState = false;

    pinMode(_pin, INPUT_PULLUP);
}

bool Button::GetState(){
    bool isPressed = GetReading();

    if(isPressed && !_lastState){
        _lastState = isPressed;
        return true;
    }

    _lastState = isPressed;
    return false;
}

bool Button::GetReading(){
    return digitalRead(_pin) == LOW;
}