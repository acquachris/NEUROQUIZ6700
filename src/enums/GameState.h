#pragma once

#include "enums\GameState.h"

namespace GameState {
    enum GameState {
        INTRO,
        MENU,

        QUESTION_GAME,
        KEYPAD_GAME,
        RFID_GAME
    };
}