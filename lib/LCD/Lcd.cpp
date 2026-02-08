#include "Arduino.h"
#include "Lcd.h"
#include "LiquidCrystal_I2C.h"

#define LCD_COLS 20
#define LCD_ROWS 4
#define MAX_TEXT_LENGTH 256
#define MAX_PAGES 32

Lcd::Lcd() : _lcd(0x27, LCD_COLS, LCD_ROWS){
    
}

void Lcd::Init(){
    Serial.println("Initializing LCD");
    _lcd.init();
    _lcd.backlight();
    Serial.println("LCD Initialized");
}

void Lcd::Clear(bool shouldDisablePaging) {
    if(shouldDisablePaging){
        _pagingEnabled = false;
    }

    _lcd.clear();
}

void Lcd::ClearLine(int line){
    _pagingEnabled = false;

    FillLine(line, ' ');
}

void Lcd::Write(const char* text) {
    _pagingEnabled = false;

    _lcd.print(text);
}

void Lcd::WriteLine(const char* text, int line, bool shouldDisablePaging) {
    if(shouldDisablePaging){
        _pagingEnabled = false;
    }

    _lcd.setCursor(0, line);
    _lcd.print(text);
}

void Lcd::FillLine(int line, char character) {
    _pagingEnabled = false;

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

void Lcd::SetPages(const char** pages, int pageCount, int currentPage = 0) {
    if (!pages || pageCount <= 0) {
        _pagingEnabled = false;
        return;
    }

    _pages = pages;
    _pageCount = pageCount;
    _currentPage = currentPage;
    _pagingEnabled = true;

    SafeWrite(_pages[_currentPage], false, false);
}

void Lcd::MovePage(bool right) {
    
    if (!_pagingEnabled) return;
    if (!_pages || _pageCount <= 1) return;

    if (right) {
        _currentPage++;
        if (_currentPage >= _pageCount) {
            _currentPage = 0;
        }
    } else {
        _currentPage--;
        if (_currentPage < 0) {
            _currentPage = _pageCount - 1;
        }
    }

    SafeWrite(_pages[_currentPage], false, false);
}

// Si ringrazia il compagno ChatGPT e Claude AI per i seguenti metodi.
// Ammetto di essere troppo pigro per scrivere metodi così farraginosi
// Giuro che non uso più AI (forse :D)
// Se stai leggendo, ciao :)
void Lcd::WriteCentered(const char* line1, const char* line2) {
    _pagingEnabled = false;

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

void Lcd::SafeWrite(const char* text, bool allowWordSplit, bool shouldDisablePaging) {
    if (!text) return;
    
    Clear(shouldDisablePaging);

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
            WriteLine(ptr, line, shouldDisablePaging);
            line++;
            break;
        }

        // Line too long
        if (!allowWordSplit) {
            // Try to find the last space within lcdCols
            int splitPos = lcdCols;
            
            // Check if character at lcdCols position is a space
            if (ptr[lcdCols] == ' ') {
                // Perfect fit - word ends exactly at column boundary
                splitPos = lcdCols;
            } else {
                // Look backwards for a space
                while (splitPos > 0 && ptr[splitPos] != ' ') {
                    splitPos--;
                }
                if (splitPos == 0) splitPos = lcdCols; // no space found, forced split
            }

            char temp[lcdCols + 1];
            strncpy(temp, ptr, splitPos);
            temp[splitPos] = '\0';
            WriteLine(temp, line, shouldDisablePaging);
            line++;

            // Skip the split position and any following spaces
            ptr += splitPos;
            while (*ptr == ' ') ptr++;
        } else {
            // Forced split
            char temp[lcdCols + 1];
            strncpy(temp, ptr, lcdCols);
            temp[lcdCols] = '\0';
            WriteLine(temp, line, shouldDisablePaging);
            line++;
            ptr += lcdCols;
        }
    }
}

bool Lcd::TextFitsInLcd(const char* text, bool allowWordSplit) {
    if (!text) return true;

    const int lcdCols = 20;
    const int lcdRows = 4;

    // Working copy
    char buffer[256];
    strncpy(buffer, text, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    int usedLines = 0;
    char* ptr = buffer;

    while (*ptr) {
        if (usedLines >= lcdRows) {
            return false; // no more space
        }

        int len = strlen(ptr);

        if (len <= lcdCols) {
            usedLines++;
            break;
        }

        if (!allowWordSplit) {
            int splitPos = lcdCols;
            while (splitPos > 0 && ptr[splitPos] != ' ') {
                splitPos--;
            }
            if (splitPos == 0) splitPos = lcdCols;

            ptr += splitPos;
            while (*ptr == ' ') ptr++;
        } else {
            ptr += lcdCols;
        }

        usedLines++;
    }

    return usedLines <= lcdRows;
}

// Arrivato a questo punto del progetto mi sono esaurito
// Per favore voglio finire al più presto
// Aiuto
// ~ Christian - 05/02/2026 14:48

// EVVAI IMPLEMENTIAMO L'ENNESIMO METODO IN QUESTA CLASSE CHE PER L'ARMORE DI DIO
// È LA COSA PIU ORRIBILE DI QUESTO MONDO

// Aggiornamento del 07/02/2026
// Dopo ore sono riuscito a far funzionare sta merda
// Si ringrazia profondamente Gemini per il supporto.
char** Lcd::CreatePagesFromText(const char* text, int* pageCount) {
    if (!text || text[0] == '\0') {
        if (pageCount) *pageCount = 0;
        return nullptr;
    }

    const int lcdCols = 20;
    const int lcdRows = 4;
    const int maxCharsPerPage = lcdCols * lcdRows;

    static char pageStorage[MAX_PAGES][maxCharsPerPage + 1];
    static char* pagePointers[MAX_PAGES];

    // Init storage
    for (int i = 0; i < MAX_PAGES; i++) {
        pagePointers[i] = pageStorage[i];
        pageStorage[i][0] = '\0';
    }

    int pageIndex = 0;
    const char* ptr = text;

    while (*ptr && pageIndex < MAX_PAGES) {
        char* page = pageStorage[pageIndex];
        int pageCharCount = 0;

        for (int row = 0; row < lcdRows && *ptr; row++) {

            int remainingTextLen = strlen(ptr);
            int charsToTake = lcdCols;

            if (remainingTextLen <= lcdCols) {
                charsToTake = remainingTextLen;
            } else {
                // Look backwards from position lcdCols-1 for a space
                int splitPos = lcdCols - 1;
                while (splitPos > 0 && ptr[splitPos] != ' ') {
                    splitPos--;
                }
                
                if (splitPos > 0) {
                    // Found a space - split there (don't include the space)
                    charsToTake = splitPos;
                } else {
                    // No space found - forced split at lcdCols
                    charsToTake = lcdCols;
                }
            }

            // Copy text
            strncpy(page + pageCharCount, ptr, charsToTake);
            pageCharCount += charsToTake;
            ptr += charsToTake;

            // Skip spaces for next line
            while (*ptr == ' ') ptr++;

            // Pad rest of line with spaces
            while (pageCharCount % lcdCols != 0) {
                page[pageCharCount++] = ' ';
            }
        }

        page[pageCharCount] = '\0';
        pageIndex++;
    }

    if (pageCount) *pageCount = pageIndex;
    return pagePointers;
}