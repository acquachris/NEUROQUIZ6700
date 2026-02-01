#include "structs/Hardware.h"
#include "enums/GameState.h"

class Menu {
    private:
        Hardware::Hardware& hw;
        
        void HandleMenuClose();

    public:
        Menu(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
};