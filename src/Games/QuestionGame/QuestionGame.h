#include "structs/Hardware.h"

class QuestionGame {
    public:
        enum GameStatus {
            INTRO,
            ANSWERING,
            ANSWER,
            RESULTS,
            EXIT
        };

        enum QuestionState {
            QUESTION = -1,
            ANSWER_A = 0,
            ANSWER_B = 1,
            ANSWER_C = 2,
            ANSWER_D = 3
        };

    private:
        Hardware::Hardware& hw;

        GameStatus gameStatus;
        QuestionState questionState;

        int pageCount = 0;
        int currentPageNumber = 0;

        int wrongAnswers;
        int correctAnswers;
        int currentQuestionNumber;
        int lastQuestionNuimber;

        long lastPressTime = 0;

        void PromptQuestion(int questionNumber);
        void CheckForQuestionChange();
        void CheckForAnswer();
        void ShowAnswer(bool wasCorrect, char selectedAnswer, char correctAnswer);
        void ShowResults();
        void HandleArrowButtons();
        void SetLedStatus(char letter, bool isGreen, bool isOn);
        void DisableAllLeds();

    public:
        QuestionGame(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
};