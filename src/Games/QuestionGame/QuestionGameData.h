#ifndef QUESTION_GAME_DATA_H
#define QUESTION_GAME_DATA_H

#include <avr/pgmspace.h>

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
    inline const int questionsLength = 22;

    // Question 1
    const char q1_text[] PROGMEM = "Quale delle seguenti strutture NON fa parte delle meningi, le membrane protettive del Sistema Nervoso Centrale?";
    const char q1_a[] PROGMEM = "Dura madre";
    const char q1_b[] PROGMEM = "Aracnoide";
    const char q1_c[] PROGMEM = "Pia madre";
    const char q1_d[] PROGMEM = "Talamo";

    // Question 2
    const char q2_text[] PROGMEM = "Qual e' la funzione principale della barriera emato-encefalica?";
    const char q2_a[] PROGMEM = "Ammortizzare gli urti meccanici";
    const char q2_b[] PROGMEM = "Proteggere il tessuto nervoso da sostanze potenzialmente dannose nel sangue";
    const char q2_c[] PROGMEM = "Produrre liquido cefalorachidiano";
    const char q2_d[] PROGMEM = "Trasmettere rapidamente gli impulsi nervosi";

    // Question 3
    const char q3_text[] PROGMEM = "Cosa caratterizza principalmente la sostanza bianca del SNC?";
    const char q3_a[] PROGMEM = "E' formata dai corpi cellulari dei neuroni";
    const char q3_b[] PROGMEM = "E' costituita da assoni mielinizzati che formano vie di comunicazione";
    const char q3_c[] PROGMEM = "Si trova sempre all'esterno nell'encefalo";
    const char q3_d[] PROGMEM = "E' il luogo principale dell'elaborazione cosciente";

    // Question 4
    const char q4_text[] PROGMEM = "Quale parte del Sistema Nervoso Periferico e' responsabile della preparazione del corpo all'azione nello stress (reazione \"attacco o fuga\")?";
    const char q4_a[] PROGMEM = "Sistema Nervoso Somatico";
    const char q4_b[] PROGMEM = "Sistema Nervoso Parasimpatico";
    const char q4_c[] PROGMEM = "Sistema Nervoso Simpatico";
    const char q4_d[] PROGMEM = "Nervi cranici";

    // Question 5
    const char q5_text[] PROGMEM = "Cosa si trova all'interno della radice dorsale di un nervo spinale?";
    const char q5_a[] PROGMEM = "Corpi cellulari dei motoneuroni";
    const char q5_b[] PROGMEM = "Fibre nervose sensoriali (che portano informazioni verso il midollo)";
    const char q5_c[] PROGMEM = "Solo fibre del sistema simpatico";
    const char q5_d[] PROGMEM = "Liquido cefalorachidiano";

    // Question 6
    const char q6_text[] PROGMEM = "Quale componente dell'encefalo e' considerata il \"Maestro della Coordinazione\", indispensabile per l'equilibrio e l'apprendimento motorio?";
    const char q6_a[] PROGMEM = "Diencefalo";
    const char q6_b[] PROGMEM = "Tronco Encefalico";
    const char q6_c[] PROGMEM = "Cervelletto";
    const char q6_d[] PROGMEM = "Telencefalo";

    // Question 7
    const char q7_text[] PROGMEM = "Quanti neuroni ospita mediamente l'encefalo umano secondo le slide?";
    const char q7_a[] PROGMEM = "Circa 100 trilioni";
    const char q7_b[] PROGMEM = "Circa 86 miliardi";
    const char q7_c[] PROGMEM = "Quasi 1,4 milioni";
    const char q7_d[] PROGMEM = "Circa 2 miliardi";

    // Question 8
    const char q8_text[] PROGMEM = "Quale struttura funge da stazione di smistamento delle informazioni tra cervello, tronco encefalico e midollo spinale, regolando anche il ciclo sonno-veglia?";
    const char q8_a[] PROGMEM = "Diencefalo";
    const char q8_b[] PROGMEM = "Sostanza Bianca";
    const char q8_c[] PROGMEM = "Cervelletto";
    const char q8_d[] PROGMEM = "Ossa del cranio";

    // Question 9
    const char q9_text[] PROGMEM = "Cos'e' la \"Sostanza Bianca\" a livello microscopico?";
    const char q9_a[] PROGMEM = "L'insieme dei corpi cellulari dei neuroni";
    const char q9_b[] PROGMEM = "Una membrana protettiva delle meningi";
    const char q9_c[] PROGMEM = "Il fluido che ammortizza l'encefalo";
    const char q9_d[] PROGMEM = "Il \"cablaggio\" composto da assoni mielinizzati per la comunicazione tra le aree";

    // Question 10
    const char q10_text[] PROGMEM = "Qual e' la funzione principale dei dendriti all'interno di un neurone?";
    const char q10_a[] PROGMEM = "Trasportare l'impulso nervoso in uscita verso altri neuroni o muscoli";
    const char q10_b[] PROGMEM = "Ricevere informazioni in entrata e convogliarle al corpo cellulare";
    const char q10_c[] PROGMEM = "Produrre la guaina mielinica per isolare l'assone";
    const char q10_d[] PROGMEM = "Contenere il nucleo e i principali organuli cellulari";

    // Question 11
    const char q11_text[] PROGMEM = "Quali neuroni trasportano i segnali dal Sistema Nervoso Centrale verso i muscoli?";
    const char q11_a[] PROGMEM = "Neuroni sensitivi (afferenti)";
    const char q11_b[] PROGMEM = "Interneuroni";
    const char q11_c[] PROGMEM = "Motoneuroni (efferenti)";
    const char q11_d[] PROGMEM = "Neuroni anassonici";

    // Question 12
    const char q12_text[] PROGMEM = "Che cos'e' la conduzione saltatoria e da cosa e' permessa?";
    const char q12_a[] PROGMEM = "Movimento dei neuroni verso i muscoli tramite cellule gliali";
    const char q12_b[] PROGMEM = "Produzione di nuovi neuroni nell'ippocampo";
    const char q12_c[] PROGMEM = "L'impulso salta da un nodo di Ranvier all'altro";
    const char q12_d[] PROGMEM = "Degradazione della mielina che rallenta i segnali";

    // Question 13
    const char q13_text[] PROGMEM = "Quale malattia e' causata dal danneggiamento della guaina mielinica da parte del sistema immunitario?";
    const char q13_a[] PROGMEM = "Sclerosi multipla";
    const char q13_b[] PROGMEM = "Malattia di Parkinson";
    const char q13_c[] PROGMEM = "Malattia di Alzheimer";
    const char q13_d[] PROGMEM = "Sclerosi Laterale Amiotrofica (SLA)";

    // Question 14
    const char q14_text[] PROGMEM = "Cosa avviene nello spazio intersinaptico durante la trasmissione chimica?";
    const char q14_a[] PROGMEM = "Il potenziale d'azione passa direttamente da un neurone all'altro attraverso giunzioni comunicanti.";
    const char q14_b[] PROGMEM = "I neurotrasmettitori rilasciati dalla cella presinaptica diffondono verso la cellula postsinaptica.";
    const char q14_c[] PROGMEM = "I canali ionici si chiudono impedendo la depolarizzazione";
    const char q14_d[] PROGMEM = "La cellula postsinaptica libera neurotrasmettitori che tornano indietro.";

    // Question 15
    const char q15_text[] PROGMEM = "Cosa caratterizza principalmente una sinapsi elettrica?";
    const char q15_a[] PROGMEM = "La presenza di uno spazio intersinaptico ampio.";
    const char q15_b[] PROGMEM = "Il coinvolgimento di neurotrasmettitori.";
    const char q15_c[] PROGMEM = "La trasmissione continua e senza interruzione del potenziale d'azione.";
    const char q15_d[] PROGMEM = "L'effetto solo inibitorio sulla cellula postsinaptica.";

    // Question 16
    const char q16_text[] PROGMEM = "Quale dei seguenti gruppi di neurotrasmettitori comprende le endorfine?";
    const char q16_a[] PROGMEM = "Amminoacidi";
    const char q16_b[] PROGMEM = "Ammine biogene";
    const char q16_c[] PROGMEM = "Neuropeptidi";
    const char q16_d[] PROGMEM = "Neurotrasmettitori gassosi";

    // Question 17
    const char q17_text[] PROGMEM = "Cosa accade ai neurotrasmettitori dopo aver svolto il loro compito nella trasmissione chimica?";
    const char q17_a[] PROGMEM = "Si duplicano";
    const char q17_b[] PROGMEM = "Vengono distrutti sempre e solo dal sistema immunitario";
    const char q17_c[] PROGMEM = "Rimangono per sempre nella fessura sinaptica per mantenere attiva la comunicazione.";
    const char q17_d[] PROGMEM = "Sono rapidamente rimossi per arrestarne gli effetti.";

    // Question 18
    const char q18_text[] PROGMEM = "In condizioni di riposo, la differenza di carica tra l'interno e l'esterno dell'assone:";
    const char q18_a[] PROGMEM = "E' nulla.";
    const char q18_b[] PROGMEM = "E' positiva.";
    const char q18_c[] PROGMEM = "E' negativa.";
    const char q18_d[] PROGMEM = "E' misurata in ampere.";

    // Question 19
    const char q19_text[] PROGMEM = "La differenza di carica tra interno e esterno dell'assone e' data:";
    const char q19_a[] PROGMEM = "Dal passaggio di acqua.";
    const char q19_b[] PROGMEM = "Dalla presenza di ioni Na+ all'esterno e K+ all'interno.";
    const char q19_c[] PROGMEM = "Dal passaggio di elettroni.";
    const char q19_d[] PROGMEM = "Dalla presenza di ioni Na+ all'interno e K+ all'esterno.";

    // Question 20
    const char q20_text[] PROGMEM = "Durante la trasmissione dell'impulso nervoso si susseguono rapidamente 3 fasi. Quali sono e in che ordine avvengono?";
    const char q20_a[] PROGMEM = "Depolarizzazione, Iperpolarizzazione e Ripolarizzazione.";
    const char q20_b[] PROGMEM = "Iperpolarizzazione, Depolarizzazione e Ripolarizzazione.";
    const char q20_c[] PROGMEM = "Ripolarizzazione, Iperpolarizzazione e Depolarizzazione.";
    const char q20_d[] PROGMEM = "Iperpolarizzazione, Ripolarizzazione e Depolarizzazione.";

    // Question 21
    const char q21_text[] PROGMEM = "La trasmissione dell'impulso nervoso inizia:";
    const char q21_a[] PROGMEM = "Con l'uscita di K+.";
    const char q21_b[] PROGMEM = "Con l'ingresso di Na+.";
    const char q21_c[] PROGMEM = "Con l'azione della pompa Na+/K+.";
    const char q21_d[] PROGMEM = "Al raggiungimento del valore soglia.";

    // Question 22
    const char q22_text[] PROGMEM = "Nella trasmissione dell'impulso nervoso, uno stimolo piu' intenso:";
    const char q22_a[] PROGMEM = "Modifica l'ampiezza del potenziale d'azione.";
    const char q22_b[] PROGMEM = "Causa l'aumento del valore soglia.";
    const char q22_c[] PROGMEM = "Aumenta la frequenza con cui gli impulsi vengono trasmessi.";
    const char q22_d[] PROGMEM = "Causa l'abbassamento del valore soglia.";


    // Array of questions in PROGMEM
    const QuizQuestion questions[questionsLength] PROGMEM = {
        {
            q14_text, 
            {
                { 'a', q14_a, false }, 
                { 'b', q14_b, true }, 
                { 'c', q14_c, false }, 
                { 'd', q14_d, false }
            } 
        },
        {
            q3_text, 
            {
                { 'a', q3_a, false }, 
                { 'b', q3_b, true }, 
                { 'c', q3_c, false }, 
                { 'd', q3_d, false }
            } 
        },
        {
            q20_text,
            {
                { 'a', q20_a, true }, 
                { 'b', q20_b, false }, 
                { 'c', q20_c, false }, 
                { 'd', q20_d, false }
            }
        },
        {
            q8_text, 
            {
                { 'a', q8_a, true }, 
                { 'b', q8_b, false }, 
                { 'c', q8_c, false }, 
                { 'd', q8_d, false }
            } 
        },
        {
            q17_text, 
            {
                { 'a', q17_a, false }, 
                { 'b', q17_b, false }, 
                { 'c', q17_c, false }, 
                { 'd', q17_d, true }
            } 
        },
        {
            q1_text, 
            {
                { 'a', q1_a, false }, 
                { 'b', q1_b, false }, 
                { 'c', q1_c, false }, 
                { 'd', q1_d, true }
            } 
        },
        {
            q11_text, 
            {
                { 'a', q11_a, false }, 
                { 'b', q11_b, false }, 
                { 'c', q11_c, true }, 
                { 'd', q11_d, false }
            } 
        },
        {
            q6_text, 
            {
                { 'a', q6_a, false }, 
                { 'b', q6_b, false }, 
                { 'c', q6_c, true }, 
                { 'd', q6_d, false }
            } 
        },
        {
            q22_text,
            {
                { 'a', q22_a, false }, 
                { 'b', q22_b, false },
                { 'c', q22_c, true }, 
                { 'd', q22_d, false }
            }
        },
        {
            q9_text, 
            {
                { 'a', q9_a, false }, 
                { 'b', q9_b, false }, 
                { 'c', q9_c, false }, 
                { 'd', q9_d, true }
            } 
        },
        {
            q15_text, 
            {
                { 'a', q15_a, false }, 
                { 'b', q15_b, false }, 
                { 'c', q15_c, true }, 
                { 'd', q15_d, false }
            } 
        },
        {
            q4_text, 
            {
                { 'a', q4_a, false }, 
                { 'b', q4_b, false }, 
                { 'c', q4_c, true }, 
                { 'd', q4_d, false }
            } 
        },
        {
            q19_text,
            {
                { 'a', q19_a, false }, 
                { 'b', q19_b, true },
                { 'c', q19_c, false }, 
                { 'd', q19_d, false }
            }
        },
        {
            q2_text, 
            {
                { 'a', q2_a, false }, 
                { 'b', q2_b, true }, 
                { 'c', q2_c, false }, 
                { 'd', q2_d, false }
            } 
        },
        {
            q18_text, 
            {
                { 'a', q18_a, false }, 
                { 'b', q18_b, false }, 
                { 'c', q18_c, true }, 
                { 'd', q18_d, false }
            }
        },
        {
            q7_text, 
            {
                { 'a', q7_a, false }, 
                { 'b', q7_b, true }, 
                { 'c', q7_c, false }, 
                { 'd', q7_d, false }
            } 
        },
        {
            q12_text, 
            {
                { 'a', q12_a, false }, 
                { 'b', q12_b, false }, 
                { 'c', q12_c, true }, 
                { 'd', q12_d, false }
            } 
        },
        {
            q16_text,
            {
                { 'a', q16_a, false }, 
                { 'b', q16_b, false }, 
                { 'c', q16_c, true }, 
                { 'd', q16_d, false }
            }        
        },
        {
            q5_text, 
            {
                { 'a', q5_a, false }, 
                { 'b', q5_b, true }, 
                { 'c', q5_c, false }, 
                { 'd', q5_d, false }
            } 
        },
        {
            q10_text, 
            {
                { 'a', q10_a, false }, 
                { 'b', q10_b, true }, 
                { 'c', q10_c, false }, 
                { 'd', q10_d, false }
            } 
        },
        {
            q21_text,
            {
                { 'a', q21_a, false }, 
                { 'b', q21_b, false },
                { 'c', q21_c, false }, 
                { 'd', q21_d, true }
            }
        },
        {
            q13_text, 
            {
                { 'a', q13_a, true }, 
                { 'b', q13_b, false }, 
                { 'c', q13_c, false }, 
                { 'd', q13_d, false }
            } 
        }
    };
}

#endif // QUESTION_GAME_DATA_H