struct RFIDQuestion {
    const char* text;
    const char* answerId;
};

struct CardAssociation {
    const char* cardId;
    const char* answerId;
    const char* readableAnswer;
};

namespace RFIDGameData {
    const int questionsLength = 9;
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
            readableAnswer: "Cervelletto"
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

    const RFIDQuestion questions[questionsLength] = {
        {
            "E' protetto dalle 3 meningi.",
            "cervello"
        },
        {
            "E' la porzione piu' voluminosa e specializzata, sede delle funzioni cognitive superiori.",
            "cervello"
        },
        {
            "Regola il ritmo cardiaco, la pressione arteriosa e la respirazione.",
            "tronco"
        },
        {
            "Contiene oltre il 50% di tutti i neuroni nonostante sia solo il 10% della massa.",
            "cervelletto"
        },
        {
            "Comprende il mesencefalo, il ponte di Varolio e il midollo allungato.",
            "tronco"
        },
        {
            "Indispensabile per la coordinazione dei muscoli volontari e l'equilibrio.",
            "cervelletto"
        },
        {
            "Diviso da una profonda scanalatura in due emisferi quasi simmetrici.",
            "cervello"
        },
        {
            "Funge da ponte vitale tra il cervello e il midollo spinale.",
            "tronco"
        },
        {
            "Contribuisce anche alle funzioni di attenzione e linguaggio.",
            "cervelletto"
        }
    };

    
}