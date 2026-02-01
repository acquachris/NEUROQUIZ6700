#include "Arduino.h"
#include "Lcd.h"
#include "LiquidCrystal_I2C.h"

Lcd::Lcd() : _lcd(0x27, 20, 4){
    
}

void Lcd::Init(){
    Serial.println("Initializing LCD");
    _lcd.init();
    _lcd.backlight();
    Serial.println("LCD Initialized");
}

void Lcd::Clear() {
    _lcd.clear();
}

void Lcd::Write(const char* text) {
    _lcd.print(text);
}

void Lcd::WriteLine(const char* text, int line) {
    _lcd.setCursor(0, line);
    _lcd.print(text);
}

void Lcd::FillLine(int line, char character) {
    _lcd.setCursor(0, line);
    for (int i = 0; i < 20; i++) {
        _lcd.print(character);
    }
}

void Lcd::WriteCentered(const char* line1, const char* line2) {
    Clear();

    int lcdCols = 20;
    int row1 = 1;
    int row2 = 2;

    // Calculate starting column for centering
    int startCol1 = (lcdCols - strlen(line1)) / 2;
    int startCol2 = (lcdCols - strlen(line2)) / 2;

    // Make sure it's not negative
    if (startCol1 < 0) startCol1 = 0;
    if (startCol2 < 0) startCol2 = 0;

    // Print centered lines
    FillLine(0, '=');
    FillLine(3, '=');

    _lcd.setCursor(startCol1, row1);
    _lcd.print(line1);

    _lcd.setCursor(startCol2, row2);
    _lcd.print(line2);
}
