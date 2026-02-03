struct Question {
    const char* text;
    const char* answerId;
};

struct CardAssociation {
    const char* cardId;
    const char* answerId;
    const char* readableAnswer;
};

namespace RFIDGameData {
    const int questionsLength = 1;
    const int cardAssociationsLength = 7;

    const CardAssociation cardAssociations[] = {
        {
            cardId: "17 82 45 44",
            answerId: "cervello",
            readableAnswer: "Cervello"
        },
        {
            cardId: "2D 95 3D 06",
            answerId: "cervelletto",
            readableAnswer: "cervelletto"
        },
        {
            cardId: "C7 13 96 43",
            answerId: "neuroni",
            readableAnswer: "Neuroni"
        },
        {
            cardId: "0A 9A 7C 3C",
            answerId: "sinapsi",
            readableAnswer: "Sinapsi"
        },
        {
            cardId: "BA E0 83 3C",
            answerId: "tronco",
            readableAnswer: "Tronco Encefalico"
        },
        {
            cardId: "9D F3 0A 06",
            answerId: "neuro",
            readableAnswer: "Neurotrasmettitori"
        },
        {
            cardId: "none",
            answerId: "none",
            readableAnswer: "none"
        }
    };

    const Question questions[questionsLength] = {
        {
            text: "La risposta e' il cervello.",
            answerId: "cervello"
        }
    };

    
}