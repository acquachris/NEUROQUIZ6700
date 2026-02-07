#include "Arduino.h"
#include "QuestionGame.h"
#include "structs/Hardware.h"
#include "Music.h"
#include "Games/QuestionGame/QuestionGameData.h"

#define DEBOUNCE_TIME = 50

QuestionGame::QuestionGame(Hardware::Hardware& _hw) : hw(_hw) {
    wrongQuestions = 0;
    rightQuestions = 0;
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
void QuestionGame::PromptQuestion(int questionNumber) {
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

    const char** pages = hw.lcd.CreatePagesFromText(question.text, &pageCount, true);
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
        Serial.println("===============================");

        if (questionState == QuestionState::QUESTION) {
            Serial.println("From QUESTION");
            nextQuestionState = isLeftPressed
                ? QuestionState::ANSWER_D
                : QuestionState::ANSWER_A;
        }
        else {
            Serial.println("From ANSWER");
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

        Serial.print("Current question state: ");
        Serial.println(questionState);

        Serial.print("Next question state: ");
        Serial.println(nextQuestionState);

        Serial.print("Page count: ");
        Serial.println(pageCount);

        Serial.print("Current page number: ");
        Serial.println(currentPageNumber);

        Serial.print("Next page content: ");
        Serial.println(nextQuestionState == QuestionState::QUESTION ? question.text : question.answers[nextQuestionState].text);
        Serial.println("===============================\n");


        char** pages = nextQuestionState == QuestionState::QUESTION ? 
            hw.lcd.CreatePagesFromText(question.text, &pageCount, true) : 
            hw.lcd.CreatePagesFromText(question.answers[nextQuestionState].text, &pageCount);
            
        Serial.print("Content of first element: ");
        Serial.println(pages[0]);

        currentPageNumber = isLeftPressed ? pageCount - 1 : 0;
        questionState = nextQuestionState;

        hw.lcd.SetPages(pages, pageCount, currentPageNumber);
    }else{
        Serial.println("Moving page");
        hw.lcd.MovePage(isRightPressed);
        currentPageNumber += isRightPressed ? 1 : -1;
    }   


    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;
    hw.buzzer.Play(options);
}

void QuestionGame::CheckForAnswer(){

}

void QuestionGame::ShowAnswer(bool wasCorrect){

}

void QuestionGame::ShowResults(){

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
    if(gameStatus != GameStatus::ANSWERING) return;

    CheckForQuestionChange();
    CheckForAnswer();
    HandleArrowButtons();
}

void QuestionGame::Exit() {
    wrongQuestions = 0;
    rightQuestions = 0;
    currentQuestionNumber = 0;
    lastQuestionNuimber = -1;
    gameStatus = GameStatus::EXIT;
}