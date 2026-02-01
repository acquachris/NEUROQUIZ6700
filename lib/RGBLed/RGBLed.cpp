#include "Arduino.h"
#include "RGBLed.h"

RGBLed::RGBLed(int pinR, int pinG, int pinB){
    _pinR = pinR;
    _pinG = pinG;
    _pinB = pinB;

    pinMode(_pinR, OUTPUT);
    pinMode(_pinG, OUTPUT);
    pinMode(_pinB, OUTPUT);
}

void RGBLed::SetColor(int r, int g, int b){
    _lastR = r;
    _lastG = g;
    _lastB = b;

    analogWrite(_pinR, r);
    analogWrite(_pinG, g);
    analogWrite(_pinB, b);
}

void RGBLed::On(){
    pinMode(_pinR, _lastR);
    pinMode(_pinG, _lastB);
    pinMode(_pinB, _lastG);
}

void RGBLed::Off(){
    pinMode(_pinR, LOW);
    pinMode(_pinG, LOW);
    pinMode(_pinB, LOW);
}