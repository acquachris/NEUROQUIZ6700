#include "structs/Hardware.h"
#include "enums/GameState.h"

class KeypadGame {
    public:
        enum GameStatus {
            INTRO,
            INSERTING,
            ANSWER,
            EXIT,
            AWAITING_RETRY
        };

    private:
        Hardware::Hardware& hw;
        
        char answer[17];

        int numberOfTries = 1;
        
        void PromptQuestion(int number);
        void CheckKeypad();
        void CheckAnswer();
        void ShowAnswer(bool isCorrect);
        void CheckForRetry();
        void UpdateLcd();
        void ClearAnswerFromMemory();
        void ShowInstructions();
        
        GameStatus gameStatus = GameStatus::INTRO;

    public:
        KeypadGame(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
};