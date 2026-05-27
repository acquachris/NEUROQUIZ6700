#include "structs/Hardware.h"
#include "enums/GameState.h"

class Menu {
    private:
        Hardware::Hardware& hw;

        int currentNote;
        int currentMenuIndex = 0;
        bool menuLoaded = false;

        void HandleMenuClose();

    public:
        Menu(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
        int GetCurrentMenuIndex();
};