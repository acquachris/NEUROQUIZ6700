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
    inline const int questionsLength = 13;

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

    // Array of questions in PROGMEM
    const QuizQuestion questions[questionsLength] PROGMEM = {
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
            q2_text, 
            {
                { 'a', q2_a, false }, 
                { 'b', q2_b, true }, 
                { 'c', q2_c, false }, 
                { 'd', q2_d, false }
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
            q4_text, 
            {
                { 'a', q4_a, false }, 
                { 'b', q4_b, false }, 
                { 'c', q4_c, true }, 
                { 'd', q4_d, false }
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
            q6_text, 
            {
                { 'a', q6_a, false }, 
                { 'b', q6_b, false }, 
                { 'c', q6_c, true }, 
                { 'd', q6_d, false }
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
            q8_text, 
            {
                { 'a', q8_a, true }, 
                { 'b', q8_b, false }, 
                { 'c', q8_c, false }, 
                { 'd', q8_d, false }
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
            q10_text, 
            {
                { 'a', q10_a, false }, 
                { 'b', q10_b, true }, 
                { 'c', q10_c, false }, 
                { 'd', q10_d, false }
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
            q12_text, 
            {
                { 'a', q12_a, false }, 
                { 'b', q12_b, false }, 
                { 'c', q12_c, true }, 
                { 'd', q12_d, false }
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