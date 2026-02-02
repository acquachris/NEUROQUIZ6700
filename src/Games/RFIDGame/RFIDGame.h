#include "structs/Hardware.h"
#include "enums/GameState.h"

class RFIDGame {
    public:
        enum GameStatus {
            INTRO,
            QUESTION,
            ANSWER,
            RESULT,
            EXIT
        };

    private:
        Hardware::Hardware& hw;
        
        const char* ReadCard();
        
        void PromptQuestion(int number);
        void CheckForQuestionChange();
        void CheckForAnswer();
        void ShowAnswer(bool wasCorrect);
        void ShowResults();

        int currentQuestionNumber = 0;
        int lastQuestionNumber = -1;

        int correctAnswers = 0;
        int wrongAnswers = 0;

        GameStatus gameStatus = GameStatus::INTRO;

    public:
        RFIDGame(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
};