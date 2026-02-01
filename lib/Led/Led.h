#pragma once

class Led {
    private:
        int _pin;
        bool _state;

    public:
        Led(int pin);
        Led(int pin, bool state);

        bool GetState();

        void On();
        void Off();
        void SetState(bool state);
};