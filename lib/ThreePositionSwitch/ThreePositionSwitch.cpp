#include "Arduino.h"
#include "ThreePositionSwitch.h"

ThreePositionSwitch::ThreePositionSwitch(int leftPin, int rightPin){
    _leftPin = leftPin;
    _pinRight = rightPin;

    pinMode(_leftPin, INPUT_PULLUP);
    pinMode(_pinRight, INPUT_PULLUP);

    lastPosition = UNCHANGED;
}

ThreePositionSwitch::Position ThreePositionSwitch::GetReading(){
    if(digitalRead(_leftPin) == LOW){
        return LEFT;
    }
    else if(digitalRead(_pinRight) == LOW){
        return RIGHT;
    }
    else{
        return CENTER;
    }
}

ThreePositionSwitch::Position ThreePositionSwitch::GetPosition(){
    Position currentPosition = GetReading();

    if(currentPosition != lastPosition){
        lastPosition = currentPosition;
        return currentPosition;
    }
    
    return UNCHANGED;
}

void ThreePositionSwitch::Reset(){
    lastPosition = RESET;
}