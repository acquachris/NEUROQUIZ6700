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
    inline const int questionsLength = 13;
    
    const char* questionDividerPage =
        "====================      RISPOSTE                          ====================";

    inline const QuizQuestion questions[questionsLength] = {
        {
            "Quale delle seguenti strutture NON fa parte delle meningi, le membrane protettive del Sistema Nervoso Centrale?",
            {
                { 'a', "Dura madre", false },
                { 'b', "Aracnoide", false },
                { 'c', "Pia madre", false },
                { 'd', "Talamo", true }
            }
        },

        {
            "Qual e' la funzione principale della barriera emato-encefalica?",
            {
                { 'a', "Ammortizzare gli urti meccanici", false },
                { 'b', "Proteggere il tessuto nervoso da sostanze potenzialmente dannose nel sangue", true },
                { 'c', "Produrre liquido cefalorachidiano", false },
                { 'd', "Trasmettere rapidamente gli impulsi nervosi", false }
            }
        },

        {
            "Cosa caratterizza principalmente la sostanza bianca del SNC?",
            {
                { 'a', "E' formata dai corpi cellulari dei neuroni", false },
                { 'b', "E' costituita da assoni mielinizzati che formano vie di comunicazione", true },
                { 'c', "Si trova sempre all'esterno nell'encefalo", false },
                { 'd', "E' il luogo principale dell'elaborazione cosciente", false }
            }
        },

        {
            "Quale parte del Sistema Nervoso Periferico e' responsabile della preparazione del corpo all'azione nello stress (reazione \"attacco o fuga\")?",
            {
                { 'a', "Sistema Nervoso Somatico", false },
                { 'b', "Sistema Nervoso Parasimpatico", false },
                { 'c', "Sistema Nervoso Simpatico", true },
                { 'd', "Nervi cranici", false }
            }
        },

        {
            "Cosa si trova all'interno della radice dorsale di un nervo spinale?",
            {
                { 'a', "Corpi cellulari dei motoneuroni", false },
                { 'b', "Fibre nervose sensoriali (che portano informazioni verso il midollo)", true },
                { 'c', "Solo fibre del sistema simpatico", false },
                { 'd', "Liquido cefalorachidiano", false }
            }
        },

        {
            "Quale componente dell'encefalo e' considerata il \"Maestro della Coordinazione\", indispensabile per l'equilibrio e l'apprendimento motorio?",
            {
                { 'a', "Diencefalo", false },
                { 'b', "Tronco Encefalico", false },
                { 'c', "Cervelletto", true },
                { 'd', "Telencefalo", false }
            }
        },

        {
            "Quanti neuroni ospita mediamente l'encefalo umano secondo le slide?",
            {
                { 'a', "Circa 100 trilioni", false },
                { 'b', "Circa 86 miliardi", true },
                { 'c', "Quasi 1,4 milioni", false },
                { 'd', "Circa 2 miliardi", false }
            }
        },

        {
            "Quale struttura funge da stazione di smistamento delle informazioni tra cervello, tronco encefalico e midollo spinale, regolando anche il ciclo sonno-veglia?",
            {
                { 'a', "Diencefalo", true },
                { 'b', "Sostanza Bianca", false },
                { 'c', "Cervelletto", false },
                { 'd', "Ossa del cranio", false }
            }
        },

        {
            "Cos'e' la \"Sostanza Bianca\" a livello microscopico?",
            {
                { 'a', "L'insieme dei corpi cellulari dei neuroni", false },
                { 'b', "Una membrana protettiva delle meningi", false },
                { 'c', "Il fluido che ammortizza l'encefalo", false },
                { 'd', "Il \"cablaggio\" composto da assoni mielinizzati per la comunicazione tra le aree", true }
            }
        },

        // NUOVE DOMANDE
        {
            "Qual e' la funzione principale dei dendriti all'interno di un neurone?",
            {
                { 'a', "Trasportare l'impulso nervoso in uscita verso altri neuroni o muscoli", false },
                { 'b', "Ricevere informazioni in entrata e convogliarle al corpo cellulare", true },
                { 'c', "Produrre la guaina mielinica per isolare l'assone", false },
                { 'd', "Contenere il nucleo e i principali organuli cellulari", false }
            }
        },

        {
            "Quali neuroni trasportano i segnali dal Sistema Nervoso Centrale verso i muscoli?",
            {
                { 'a', "Neuroni sensitivi (afferenti)", false },
                { 'b', "Interneuroni", false },
                { 'c', "Motoneuroni (efferenti)", true },
                { 'd', "Neuroni anassonici", false }
            }
        },

        {
            "Che cos'e' la conduzione saltatoria e da cosa e' permessa?",
            {
                { 'a', "Movimento dei neuroni verso i muscoli tramite cellule gliali", false },
                { 'b', "Produzione di nuovi neuroni nell'ippocampo", false },
                { 'c', "L'impulso salta da un nodo di Ranvier all'altro", true },
                { 'd', "Degradazione della mielina che rallenta i segnali", false }
            }
        },

        {
            "Quale malattia e' causata dal danneggiamento della guaina mielinica da parte del sistema immunitario?",
            {
                { 'a', "Sclerosi multipla", true },
                { 'b', "Malattia di Parkinson", false },
                { 'c', "Malattia di Alzheimer", false },
                { 'd', "Sclerosi Laterale Amiotrofica (SLA)", false }
            }
        }
    };
}
