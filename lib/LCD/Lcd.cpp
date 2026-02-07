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

    Serial.println(_pages[_currentPage]);

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

    Serial.print("printing: ");
    Serial.println(_pages[_currentPage]);

    Serial.print("Current page: ");
    Serial.println(_currentPage);

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
    Serial.print("From SafeWrite: ");
    Serial.println(text);

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
            while (splitPos > 0 && ptr[splitPos] != ' ') {
                splitPos--;
            }
            if (splitPos == 0) splitPos = lcdCols; // no space found, forced split

            char temp[lcdCols + 1];
            strncpy(temp, ptr, splitPos);
            temp[splitPos] = '\0';
            WriteLine(temp, line, shouldDisablePaging);
            line++;

            // Skip spaces for next line
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
char** Lcd::CreatePagesFromText(const char* text, int* pageCount, bool allowWordSplit) {
    if (!text || strlen(text) == 0) {
        if (pageCount) *pageCount = 0;
        return nullptr;
    }

    // We wrap the single text pointer into an array so we can reuse 
    // the logic you already have in CreatePagesFromSections.
    const char* sections[1];
    sections[0] = text;

    // Note: CreatePagesFromSections currently uses its own internal 
    // word-split logic. If you want to strictly honor 'allowWordSplit',
    // you'd need to modify the section logic, but for now, this 
    // will get your pages generated correctly!
    return CreatePagesFromSections(sections, 1, pageCount);
}

// Ciò che state per leggere è stato CHIARAMENTE generato da un'IA.
// Non sono più in condizione di scrivere qualcosa di sensato che funzioni
// Dio perdonami per questa atrocità, ma funziona e dopo una settimana di lavoro
// va più che bene. Spero che il caro prof. Tinari non legga mai questa cosa.
char** Lcd::CreatePagesFromSections(const char** sections, int sectionCount, int* pageCount) {
    if (!sections || sectionCount == 0) {
        if (pageCount) *pageCount = 0;
        return nullptr;
    }

    const int lcdCols = 20;
    const int lcdRows = 4;
    const int maxCharsPerPage = lcdCols * lcdRows; // 80 chars per page
    
    static char pageStorage[50][maxCharsPerPage + 1]; // Increased from MAX_PAGES
    static char* pagePointers[50];
    
    // Initialize pointers
    for (int i = 0; i < 50; i++) {
        pagePointers[i] = pageStorage[i];
        pageStorage[i][0] = '\0';
    }
    
    int pageIndex = 0;
    
    // Process each section separately
    for (int sectionIdx = 0; sectionIdx < sectionCount; sectionIdx++) {
        const char* text = sections[sectionIdx];
        if (!text || text[0] == '\0') continue;
        
        // Calculate length dynamically
        int textLen = strlen(text);
        
        // Create a working copy
        char* buffer = new char[textLen + 1];
        strcpy(buffer, text);
        
        char* ptr = buffer;
        
        // Fill pages for this section
        while (*ptr && pageIndex < 50) {
            char* currentPage = pageStorage[pageIndex];
            int pageCharCount = 0;
            int linesInPage = 0;
            
            // Fill the current page (max 4 lines)
            while (*ptr && linesInPage < lcdRows && pageCharCount < maxCharsPerPage) {
                int remainingInPage = maxCharsPerPage - pageCharCount;
                int remainingText = strlen(ptr);
                
                if (remainingText <= lcdCols && remainingInPage >= remainingText) {
                    // Remaining text fits in one line
                    strcpy(currentPage + pageCharCount, ptr);
                    pageCharCount += remainingText;
                    
                    // Pad remaining space in line with spaces
                    while ((pageCharCount % lcdCols) != 0 && pageCharCount < maxCharsPerPage) {
                        currentPage[pageCharCount++] = ' ';
                    }
                    
                    ptr += remainingText;
                    linesInPage++;
                    break;
                }
                
                int charsToTake = (remainingInPage < lcdCols) ? remainingInPage : lcdCols;
                
                // Find last space within line length to avoid splitting words
                int splitPos = charsToTake;
                if (charsToTake == lcdCols && remainingText > lcdCols) {
                    while (splitPos > 0 && ptr[splitPos] != ' ') {
                        splitPos--;
                    }
                    if (splitPos == 0) splitPos = charsToTake; // No space found, force split
                }
                charsToTake = splitPos;
                
                // Copy line to page
                strncpy(currentPage + pageCharCount, ptr, charsToTake);
                pageCharCount += charsToTake;
                
                // Pad rest of line with spaces
                while ((pageCharCount % lcdCols) != 0 && pageCharCount < maxCharsPerPage) {
                    currentPage[pageCharCount++] = ' ';
                }
                
                ptr += charsToTake;
                
                // Skip spaces at start of next line
                while (*ptr == ' ') ptr++;
                
                linesInPage++;
            }
            
            currentPage[pageCharCount] = '\0';
            pageIndex++;
        }
        
        delete[] buffer;
        
        // Force new page for next section (answer separation)
        // This is already handled by the outer loop structure
    }
    
    if (pageCount) {
        *pageCount = pageIndex;
    }
    
    return pagePointers;
}