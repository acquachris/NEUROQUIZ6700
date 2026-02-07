#pragma once
#include "../lib/pitches.h"

namespace Music {
    const int CorrectMusic[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6};
    const int WrongMusic[]   = {NOTE_C5, NOTE_FS4, NOTE_DS4, NOTE_C4};

    const int Beep[] = {NOTE_A5};

    const int RFIDMusic[] = {
        NOTE_E5, NOTE_G5, NOTE_A5,
        NOTE_E6,
        NOTE_A5, NOTE_G5
    };

    const int KeypadMusic[] = {
        NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4,
        NOTE_E4, NOTE_D4
    };

    const int QuizMusic[] = {
        NOTE_C5, NOTE_G4, NOTE_C5,
        NOTE_E5, NOTE_G5
    };
}