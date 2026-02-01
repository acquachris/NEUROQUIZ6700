class QuestionGame {
    private:
        int wrongQuestions;
        int rightQuestions;
        int currentQuestion;

    public:
        enum State {
            INTERMISSION,
            QUESTION,
            ANSWER
        };

        QuestionGame();

        void Init();
        void Tick();
};