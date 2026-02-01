#pragma once

#include "LiquidCrystal_I2C.h"

class Lcd {
    private:
        LiquidCrystal_I2C _lcd;

    public:
        Lcd();

        void Init();
        LiquidCrystal_I2C GetInstance();

        void Clear();
        void Write(const char* text);
        void WriteLine(const char* text, int line);
        void FillLine(int line, char character);
        void WriteCentered(const char* line1, const char* line2);
};