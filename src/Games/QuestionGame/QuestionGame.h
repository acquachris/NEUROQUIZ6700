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

    private:
        Hardware::Hardware& hw;

        GameStatus gameStatus;

        int wrongQuestions;
        int rightQuestions;
        int currentQuestionNumber;
        int lastQuestionNuimber;

        void PromptQuestion(int questionNumber);
        void CheckForQuestionChange();
        void CheckForAnswer();
        void ShowAnswer(bool wasCorrect);
        void ShowResults();
        void HandleArrowButtons();

    public:
        QuestionGame(Hardware::Hardware& _hw);

        void Init();
        void Tick();
        void Exit();
};