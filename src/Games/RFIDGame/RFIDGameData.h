struct Question {
    const char* text;
    const char* cardId;
};

namespace RFIDGameData {
    const int questionsLength = 1;

    const Question questions[questionsLength] = {
        {
            text: "ciao",
            cardId: "ciaoo"
        }
    };

    
}