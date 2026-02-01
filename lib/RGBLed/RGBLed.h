#pragma once

class RGBLed {
    private:
        int _pinR;
        int _pinG;
        int _pinB;

        int _lastR;
        int _lastG;
        int _lastB;

    public:
        RGBLed(int pinR, int pinG, int pinB);

        void SetColor(int r, int g, int b);
        void On();
        void Off();
};