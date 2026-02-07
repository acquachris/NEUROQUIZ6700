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
            "In questa domanda THE risposta corretta sara' la lettera C! Evviva 1 2 3 4 5 6 7 8 9 10!",
            {
                { 'a', "Risposta A LUNGA MA TANTO LUNGA VEDIAMO SE FUNZIONA todos. 1 2 3 4 5 6 7 8 9 10!", false  },
                { 'b', "Risposta B", false },
                { 'c', "Risposta C", true },
                { 'd', "Risposta D Questa pure la facciamo 1 2 3 4 5 6 7 8 9 10! 9801 3301 1 4 6 87 9 5 6777", false }
            }
        }
    };
}
