struct QuizAnswer {
    char answerId;
    const char* text;
    bool isCorrect;
};

struct QuizQuestion {
    const char* text;
    const QuizAnswer answers[4];
};

namespace QuestionGameData {
    inline const int questionsLength = 1;
    
    const char* questionDividerPage = "====================      RISPOSTE                          ====================";

    inline const QuizQuestion questions[questionsLength] = {
        {
            "La risposta e' A. POI TESTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO MOLTO LUNGO",
            {
                { 'a', "Risposta A", true  },
                { 'b', "Risposta B", false },
                { 'c', "Risposta C", false },
                { 'd', "Risposta D", false }
            }
        }
    };
}
