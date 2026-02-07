#include "Arduino.h"
#include "QuestionGame.h"
#include "structs/Hardware.h"
#include "Music.h"
#include "Games/QuestionGame/QuestionGameData.h"

#define DEBOUNCE_TIME = 50

QuestionGame::QuestionGame(Hardware::Hardware& _hw) : hw(_hw) {
    wrongAnswers = 0;
    correctAnswers = 0;
    currentQuestionNumber = 0;
    lastQuestionNuimber = -1;
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
// Di conseguenza, la versione che ora leggete è completamente riscrita A MANO (fanculo alle AI)
//
// AGGIORNAMENTO 19:08
// Signori e signore, è stato un lungo pomeriggio. FUNZIONA TUTTO COME DEVE FUNZIONARE
// Però ora mi serve un oki per il mal di testa...
void QuestionGame::PromptQuestion(int questionNumber) {
    DisableAllLeds();

    const QuizQuestion question = QuestionGameData::questions[questionNumber];

    questionState = QuestionState::QUESTION;

    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;
    hw.buzzer.Play(options);

    // Set the page ONLY for the question. Answers are handled in the HandleArrowButtons function
    pageCount = 0;
    currentPageNumber = 0;
    questionState = QuestionState::QUESTION;

    const char** pages = hw.lcd.CreatePagesFromText(question.text, &pageCount);
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
        // Set the new pages
        const QuizQuestion question = QuestionGameData::questions[currentQuestionNumber];

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


        char** pages = nextQuestionState == QuestionState::QUESTION ? 
            hw.lcd.CreatePagesFromText(question.text, &pageCount) : 
            hw.lcd.CreatePagesFromText(question.answers[nextQuestionState].text, &pageCount);

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

    QuizQuestion question = QuestionGameData::questions[currentQuestionNumber];
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
    gameStatus = GameStatus::ANSWER;

    Buzzer::BuzzerPlayOptions options;
    options.notes = wasCorrect ? Music::CorrectMusic : Music::WrongMusic;
    options.size = 4;
    options.lastNoteMultiplier = 4;

    QuizQuestion question = QuestionGameData::questions[currentQuestionNumber];

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

    if(grade > 6){
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
    if(currentQuestionNumber == lastQuestionNuimber) return;

    lastQuestionNuimber = currentQuestionNumber;

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
    lastQuestionNuimber = -1;
    pageCount = 0;
    currentPageNumber = 0;
    DisableAllLeds();

    gameStatus = GameStatus::EXIT;
}