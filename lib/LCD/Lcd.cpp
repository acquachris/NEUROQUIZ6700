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

void Lcd::ClearLine(int line){
    FillLine(line, ' ');
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

    char newLine[21];

    for (int i = 0; i < 20; i++) {
        newLine[i] = character;
    }

    newLine[20] = '\0';

    _lcd.print(newLine);
}

LiquidCrystal_I2C& Lcd::GetInstance() {
    return _lcd;
}

// Si ringrazia il compagno ChatGPT e Claude AI per i seguenti.
// Ammetto di essere troppo pigro per scrivere metodi così farraginosi
// Giuro che non uso più AI (forse :D)
// Se stai leggendo, ciao :)
void Lcd::WriteCentered(const char* line1, const char* line2) {
    int lcdCols = 20;
    int row1 = 1;
    int row2 = 2;

    if (!line1) line1 = "";
    if (!line2) line2 = "";

    int len1 = strlen(line1);
    int len2 = strlen(line2);

    if (len1 > lcdCols) len1 = lcdCols;
    if (len2 > lcdCols) len2 = lcdCols;

    int startCol1 = (lcdCols - len1) / 2;
    int startCol2 = (lcdCols - len2) / 2;

    if (startCol1 < 0) startCol1 = 0;
    if (startCol2 < 0) startCol2 = 0;

    // Top and bottom borders
    FillLine(0, '=');
    FillLine(3, '=');

    // Helper buffer to ensure full line overwrite
    char buffer[lcdCols + 1];

    // --- Row 1 ---
    memset(buffer, ' ', lcdCols);
    memcpy(&buffer[startCol1], line1, len1);
    buffer[lcdCols] = '\0';
    _lcd.setCursor(0, row1);
    _lcd.print(buffer);

    // --- Row 2 ---
    memset(buffer, ' ', lcdCols);
    memcpy(&buffer[startCol2], line2, len2);
    buffer[lcdCols] = '\0';
    _lcd.setCursor(0, row2);
    _lcd.print(buffer);
}

void Lcd::SafeWrite(const char* text, bool allowWordSplit) {
    if (!text) return;

    Clear();

    int lcdCols = 20;
    int lcdRows = 4;

    // Make a working copy
    char buffer[256]; // temporary buffer for long text
    strncpy(buffer, text, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    int line = 0;
    char* ptr = buffer;

    while (*ptr && line < lcdRows) {
        int len = strlen(ptr);

        if (len <= lcdCols) {
            // Fits in one line
            WriteLine(ptr, line);
            line++;
            break;
        }

        // Line too long
        if (!allowWordSplit) {
            // Try to find the last space within lcdCols
            int splitPos = lcdCols;
            while (splitPos > 0 && ptr[splitPos] != ' ') {
                splitPos--;
            }
            if (splitPos == 0) splitPos = lcdCols; // no space found, forced split

            char temp[lcdCols + 1];
            strncpy(temp, ptr, splitPos);
            temp[splitPos] = '\0';
            WriteLine(temp, line);
            line++;

            // Skip spaces for next line
            ptr += splitPos;
            while (*ptr == ' ') ptr++;
        } else {
            // Forced split
            char temp[lcdCols + 1];
            strncpy(temp, ptr, lcdCols);
            temp[lcdCols] = '\0';
            WriteLine(temp, line);
            line++;
            ptr += lcdCols;
        }
    }
}
