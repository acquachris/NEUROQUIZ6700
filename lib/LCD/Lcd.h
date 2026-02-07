#pragma once

#include "LiquidCrystal_I2C.h"

class Lcd {
    private:
        LiquidCrystal_I2C _lcd;
        bool _pagingEnabled = false;
        const char** _pages = nullptr;
        int _pageCount = 0;
        int _currentPage = 0;


    public:
        Lcd();

        void Init();
        LiquidCrystal_I2C& GetInstance();

        void Clear(bool shouldDisablePaging = true);
        void Write(const char* text);
        void WriteLine(const char* text, int line, bool shouldDisablePaging = true);
        void FillLine(int line, char character);
        void WriteCentered(const char* line1, const char* line2);
        void ClearLine(int line);
        void SafeWrite(const char* text, bool allowWordSplit = false, bool shouldDisablePaging = true);

        void SetPages(const char** pages, int pageCount, int currentPage = 0);
        void MovePage(bool right);
        bool TextFitsInLcd(const char* text, bool allowWordSplit = false);

        char** CreatePagesFromText(const char* text, int* pageCount);
        char** CreatePagesFromSections(const char** sections, int sectionCount, int* pageCount);
};