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
            "In questa domanda la risposta e' C",
            {
                { 'a', "Risposta A 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40", false  },
                { 'b', "Risposta B", false },
                { 'c', "Risposta C", true },
                { 'd', "Risposta D", false }
            }
        }
    };
}
