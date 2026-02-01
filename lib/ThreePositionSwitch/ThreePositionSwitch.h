#pragma once

#include "Arduino.h"

class ThreePositionSwitch {
    public: 
        enum Position {
            UNCHANGED,
            LEFT,
            CENTER,
            RIGHT,
            RESET
        };
    
    private:
        int _leftPin;
        int _pinRight;

        Position lastPosition;

    public:
        

        ThreePositionSwitch(int leftPin, int rightPin);
        Position GetReading();
        Position GetPosition();
        void Reset();
};