#pragma once

class Button {
    private:
        int _pin;
        bool _isPressed;
        bool _lastState;

    public:
        Button(int pin);

        bool GetState();
        bool GetReading();
};