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
    const int questionsLength = 17;
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
            "Giunzioni specializzate che permettono la trasmissione di segnali tra un neurone all'altro.",
            "sinapsi"
        },
        {
            "E' la porzione piu' voluminosa e specializzata, sede delle funzioni cognitive superiori.",
            "cervello"
        },
        {
            "La cellula che consuma una grande quantita' di energia e, a causa della sua scarsa capacita' di riprodursi, risulta difficilmente sostituibile dal corpo una volta persa per mancanza di ossigeno o stress ossidativo.",
            "neuroni"
        },
        {
            "Comprende il mesencefalo, il ponte di Varolio e il midollo allungato.",
            "tronco"
        },
        {
            "Molecole chimiche che permettono ai neuroni di comunicare tra loro.",
            "neuro"
        },
        {
            "Diviso da una profonda scanalatura in due emisferi quasi simmetrici.",
            "cervello"
        },
        {
            "La cellula che rappresenta l'unita' funzionale del sistema nervoso ed e' specificamente destinata alla produzione e allo scambio di segnali.",
            "neuroni"
        },
        {
            "Indispensabile per la coordinazione dei muscoli volontari e l'equilibrio.",
            "cervelletto"
        },
        {
            "E' protetto dalle 3 meningi.",
            "cervello"
        },
        {
            "Funge da ponte vitale tra il cervello e il midollo spinale.",
            "tronco"
        },
        {
            "Posso essere gassosi.",
            "neuro"
        },
        {
            "Contiene oltre il 50% di tutti i neuroni nonostante sia solo il 10% della massa.",
            "cervelletto"
        },
        {
            "Contengono l'assone, cio' che permette la trasmissione dell'impulso nervoso.",
            "neuroni"
        },
        {
            "Possono essere elettriche o chimiche.",
            "sinapsi"
        },
        {
            "Regola il ritmo cardiaco, la pressione arteriosa e la respirazione.",
            "tronco"
        },
        {
            "Contribuisce anche alle funzioni di attenzione e linguaggio.",
            "cervelletto"
        },
        {
            "La cellula che viene prodotta durante il processo biologico della neurogenesi ed e' fondamentale per l'apprendimento, la memoria e la plasticita' cerebrale.",
            "neuroni"
        },
    };
}