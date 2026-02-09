#include "Arduino.h"
#include "QuestionGame.h"
#include "structs/Hardware.h"
#include "Music.h"
#include "Games/QuestionGame/QuestionGameData.h"

#define DEBOUNCE_TIME 50
#define BUFFER_SIZE 200  // Buffer per leggere le stringhe da PROGMEM

QuestionGame::QuestionGame(Hardware::Hardware& _hw) : hw(_hw) {
    wrongAnswers = 0;
    correctAnswers = 0;
    currentQuestionNumber = 0;
    lastQuestionNumber = -1;
    gameStatus = GameStatus::EXIT;
}

void QuestionGame::Init() {
    gameStatus = GameStatus::INTRO;

    hw.lcd.WriteCentered("Gioco selezionato:", "Quiz");

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::QuizMusic;
    options.size = 5;

    hw.buzzer.Play(options);
    
    delay(5000);

    options.notes = Music::Beep;
    options.size = 1;

    hw.buzzer.Play(options);

    hw.lcd.SafeWrite("Rispondi alle domande sul Sistema Nervoso!");

    delay(5000);

    gameStatus = GameStatus::ANSWERING;
}

// Helper function: leggi QuizQuestion da PROGMEM
QuizQuestion ReadQuestion(int index) {
    QuizQuestion q = {};
    memcpy_P(&q, &QuestionGameData::questions[index], sizeof(QuizQuestion));
    return q;
}

// Helper function: leggi stringa da PROGMEM in un buffer
void ReadStringFromPROGMEM(const char* progmemStr, char* buffer, size_t bufferSize) {
    strncpy_P(buffer, progmemStr, bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
}

// Diario di bordo
// Giorno 07/02/2026, ore 14:34
// Dopo diverse ore di scleri e pianti, questo metodo sta finalmente
// facendo ciò per cui era stato progettato.
// Credo di aver riaperto il buco dell'ozono con tutta la CO2 rilasciata
// dalle intelligenze artificiali che ho usato (si ringrazia Claude per l'aiuto)
// Credo che questo sia uno dei codici scritti peggiori della mia vita. Ma come si suol dire
// "Se funziona, lascialo stare".
// Dopo più di una settimana di lavoro il mio cervello è arrivato al limite, mi farò andare bene
// questa versione. Chiedo perdono per ciò che state per leggere.
//
// AGGIORNAMENTO 15:31
// Ho scoperto che i testi lunghi mandano COMPLETAMENTE in tilt il sistema. Mannaggia di quella P-
// Di conseguenza, la versione che ora leggete è completamente riscritta A MANO (fanculo alle AI)
//
// AGGIORNAMENTO 19:08
// Signori e signore, è stato un lungo pomeriggio. FUNZIONA TUTTO COME DEVE FUNZIONARE
// Però ora mi serve un oki per il mal di testa... EDIT 21:10 ho preso l'oki. va meglio...
//
// AGGIORNAMENTO 08/02/2026, ore XX:XX
// RAM finita, tutto in PROGMEM. Grazie ancora Claude!
//
// ENNESSIMO AGGIONRNAMENTO, DOMENICA 08/02/2026 ORE 12:45
// Aggiungendo le domande mi sono reso conto di un problema DISASTROSO
// Questa scheda di merda non riesce a gestire in memoria tutte le domande, perchè pesanti
// Si ringrazia l'amico ClaudeAI per avermi aiutato a salvare le domande in memoria invece che in RAM.
void QuestionGame::PromptQuestion(int questionNumber) {
    DisableAllLeds();

    QuizQuestion question = ReadQuestion(questionNumber);

    questionState = QuestionState::QUESTION;
    gameStatus = GameStatus::ANSWERING;

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;
    hw.buzzer.Play(options);

    // Set the page ONLY for the question. Answers are handled in the HandleArrowButtons function
    pageCount = 0;
    currentPageNumber = 0;
    questionState = QuestionState::QUESTION;

    // Buffer per il testo della domanda
    char textBuffer[BUFFER_SIZE];
    
    // Leggi il testo della domanda da PROGMEM
    ReadStringFromPROGMEM(question.text, textBuffer, BUFFER_SIZE);

    // Crea il prefisso
    char questionPrefix[10];
    snprintf(questionPrefix, sizeof(questionPrefix), "%d) ", questionNumber + 1);

    // Combina prefisso e testo (se c'è spazio)
    int prefixLen = strlen(questionPrefix);
    int textLen = strlen(textBuffer);
    
    if (prefixLen + textLen < BUFFER_SIZE - 1) {
        memmove(textBuffer + prefixLen, textBuffer, textLen + 1);
        memcpy(textBuffer, questionPrefix, prefixLen);
    }

    const char** pages = hw.lcd.CreatePagesFromText(textBuffer, &pageCount);
    hw.lcd.SetPages(pages, pageCount);
}

void QuestionGame::HandleArrowButtons() {
    if(gameStatus != GameStatus::ANSWERING) return;

    // Check debounce
    if(millis() - lastPressTime < 500) return;

    bool isRightPressed = hw.buttonRight.GetState();
    bool isLeftPressed = hw.buttonLeft.GetState();

    if(!isRightPressed && !isLeftPressed) return;

    // Update debounce time
    lastPressTime = millis();

    // Decide whether to move page or set new pages
    int nextTargetIndex = currentPageNumber + (isRightPressed ? 1 : -1);

    if(nextTargetIndex >= pageCount|| nextTargetIndex < 0){
        DisableAllLeds();
        // Set the new pages

        QuizQuestion question = ReadQuestion(currentQuestionNumber);

        QuestionState nextQuestionState;

        if (questionState == QuestionState::QUESTION) {
            nextQuestionState = isLeftPressed
                ? QuestionState::ANSWER_D
                : QuestionState::ANSWER_A;
        }
        else {
            if (isLeftPressed) {
                nextQuestionState = (questionState == QuestionState::ANSWER_A)
                    ? QuestionState::QUESTION
                    : QuestionState(questionState - 1);
            } else {
                nextQuestionState = (questionState == QuestionState::ANSWER_D)
                    ? QuestionState::QUESTION
                    : QuestionState(questionState + 1);
            }
        }

        if(nextQuestionState != QuestionState::QUESTION){
            SetLedStatus(question.answers[nextQuestionState].answerId, true, true);
            SetLedStatus(question.answers[nextQuestionState].answerId, false, true);
        }

        char textBuffer[BUFFER_SIZE];
        char prefix[10];
        
        if (nextQuestionState == QuestionState::QUESTION) {
            // Leggi il testo della domanda
            ReadStringFromPROGMEM(question.text, textBuffer, BUFFER_SIZE);
            snprintf(prefix, sizeof(prefix), "%d) ", currentQuestionNumber + 1);
        } else {
            // Leggi il testo della risposta
            int answerIndex = nextQuestionState - QuestionState::ANSWER_A;
            ReadStringFromPROGMEM(question.answers[answerIndex].text, textBuffer, BUFFER_SIZE);
            
            const char* answerLetters[] = {"A", "B", "C", "D"};
            snprintf(prefix, sizeof(prefix), "%s) ", answerLetters[answerIndex]);
        }

        // Combina prefisso e testo
        int prefixLen = strlen(prefix);
        int textLen = strlen(textBuffer);
        
        if (prefixLen + textLen < BUFFER_SIZE - 1) {
            memmove(textBuffer + prefixLen, textBuffer, textLen + 1);
            memcpy(textBuffer, prefix, prefixLen);
        }

        char** pages = hw.lcd.CreatePagesFromText(textBuffer, &pageCount);

        currentPageNumber = isLeftPressed ? pageCount - 1 : 0;
        questionState = nextQuestionState;

        hw.lcd.SetPages(pages, pageCount, currentPageNumber);
    }else{
        hw.lcd.MovePage(isRightPressed);
        currentPageNumber += isRightPressed ? 1 : -1;
    }   


    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;
    hw.buzzer.Play(options);
}

void QuestionGame::CheckForAnswer(){
    if(gameStatus != GameStatus::ANSWERING) return;

    bool isAAnswerPressed = hw.buttonAAnswer.GetState();
    bool isBAnswerPressed = hw.buttonBAnswer.GetState();
    bool isCAnswerPressed = hw.buttonCAnswer.GetState();
    bool isDAnswerPressed = hw.buttonDAnswer.GetState();

    if(!isAAnswerPressed && !isBAnswerPressed && !isCAnswerPressed && !isDAnswerPressed) return;

    // An answer has been pressed

    QuizQuestion question = ReadQuestion(currentQuestionNumber);
    bool wasCorrect = false;

    // Figure out which answer was given
    char selectedAnswer = 'a';

    if(isBAnswerPressed){
        selectedAnswer = 'b';
    }else if(isCAnswerPressed){
        selectedAnswer = 'c';
    }else if(isDAnswerPressed){
        selectedAnswer = 'd';
    }

    // Check if the answer is right
    char correctAnswer = 'a';
    for(int i = 0; i < 4; i++){
        if(!question.answers[i].isCorrect) continue;

        correctAnswer = question.answers[i].answerId;
        if(correctAnswer == selectedAnswer){
            wasCorrect = true;
        }

        break;
    }

    ShowAnswer(wasCorrect, selectedAnswer, correctAnswer);
}

void QuestionGame::ShowAnswer(bool wasCorrect, char selectedAnswer, char correctAnswer){
    DisableAllLeds();
    gameStatus = GameStatus::ANSWER;

    Buzzer::BuzzerPlayOptions options;
    options.notes = wasCorrect ? Music::CorrectMusic : Music::WrongMusic;
    options.size = 4;
    options.lastNoteMultiplier = 4;

    if(wasCorrect){
        hw.lcd.WriteCentered("Esatto! Complimenti!", "Risposta esatta!");

        SetLedStatus(correctAnswer, true, true);

        correctAnswers++;

        hw.buzzer.Play(options);

        delay(3000);
    }else{
        SetLedStatus(selectedAnswer, false, true);

        wrongAnswers++;

        hw.lcd.WriteCentered("No! Hai sbagliato!", "Risposta errata!");
        hw.buzzer.Play(options);

        delay(3000);

        options.notes = Music::Beep;
        options.size = 1;
        options.lastNoteMultiplier = 1;

        char answerText[12]; // Enough for "Risposta X\0"
        sprintf(answerText, "Risposta %c", toupper(correctAnswer));

        // Use these strings with your LCD function
        hw.lcd.WriteCentered("Risposta esatta:", answerText);
        SetLedStatus(correctAnswer, true, true);
        
        hw.buzzer.Play(options);

        delay(5000);
    }

    currentQuestionNumber++;
}

void QuestionGame::ShowResults() {
    gameStatus = GameStatus::RESULTS;

    DisableAllLeds();

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;

    char line[21];

    // Risposte Corrette
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte giuste: %d",
        correctAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // Risposte sbagliate
    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "Risposte errate: %d",
        wrongAnswers
    );

    hw.lcd.WriteCentered("Risultati!", line);
    delay(3000);

    // Risultato finale
    int totalAnswers = correctAnswers + wrongAnswers;

    int grade = (totalAnswers > 0)
        ? floor(correctAnswers * 10 / totalAnswers)
        : 0.0f;

    if(grade >= 6){
        SetLedStatus('a', true, true);
        SetLedStatus('b', true, true);
        SetLedStatus('c', true, true);
        SetLedStatus('d', true, true);
    }else{
        SetLedStatus('a', false, true);
        SetLedStatus('b', false, true);
        SetLedStatus('c', false, true);
        SetLedStatus('d', false, true);
    }

    options.size = 4;
    options.notes = (grade >= 6)
        ? Music::CorrectMusic
        : Music::WrongMusic;

    hw.buzzer.Play(options);

    snprintf(
        line,
        sizeof(line),
        "%d/%d (Voto: %d/10)",
        correctAnswers,
        totalAnswers,
        grade
    );

    hw.lcd.WriteCentered("Risultato finale:", line);
}

void QuestionGame::CheckForQuestionChange(){
    if(currentQuestionNumber == lastQuestionNumber) return;

    lastQuestionNumber = currentQuestionNumber;

    if(currentQuestionNumber >= QuestionGameData::questionsLength){
        ShowResults();
        return;
    }
    
    PromptQuestion(currentQuestionNumber);
}

void QuestionGame::Tick() {
    if(gameStatus != GameStatus::ANSWERING && gameStatus != GameStatus::ANSWER) return;

    CheckForQuestionChange();
    CheckForAnswer();
    HandleArrowButtons();
}

void QuestionGame::SetLedStatus(char letter, bool isGreen, bool isOn){
    switch(letter){
        case 'a':
            if(isGreen){
                hw.ledGreenA.SetState(isOn);
                break;
            }
            hw.ledRedA.SetState(isOn);
            break;
        case 'b':
            if(isGreen){
                hw.ledGreenB.SetState(isOn);
                break;
            }
            hw.ledRedB.SetState(isOn);
            break;
        case 'c':
            if(isGreen){
                hw.ledGreenC.SetState(isOn);
                break;
            }
            hw.ledRedC.SetState(isOn);
            break;
        case 'd':
            if(isGreen){
                hw.ledGreenD.SetState(isOn);
                break;
            }
            hw.ledRedD.SetState(isOn);
            break;
        default:
            break;
    }
}

void QuestionGame::DisableAllLeds(){
    hw.ledGreenA.Off();
    hw.ledRedA.Off();
    hw.ledGreenB.Off();
    hw.ledRedB.Off();
    hw.ledGreenC.Off();
    hw.ledRedC.Off();
    hw.ledGreenD.Off();
    hw.ledRedD.Off();
}

void QuestionGame::Exit() {
    wrongAnswers = 0;
    correctAnswers = 0;
    currentQuestionNumber = 0;
    lastQuestionNumber = -1;
    pageCount = 0;
    currentPageNumber = 0;
    DisableAllLeds();

    gameStatus = GameStatus::EXIT;
}