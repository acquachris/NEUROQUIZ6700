#include "Arduino.h"
#include "QuestionGame.h"
#include "structs/Hardware.h"
#include "Music.h"
#include "Games/QuestionGame/QuestionGameData.h"

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

static int CountPages(const char** pages) {
    int count = 0;
    while (pages && pages[count] != nullptr) {
        count++;
    }
    return count;
}

// todo: fix pages
void QuestionGame::PromptQuestion(int questionNumber) {
    // Get the question
    const QuizQuestion question = QuestionGameData::questions[questionNumber];

    // Play a beep to signal a new question
    Buzzer::BuzzerPlayOptions options;
    options.notes = Music::Beep;
    options.size = 1;
    hw.buzzer.Play(options);

    // Build complete text with all sections
    static char fullText[1024]; // Adjust size as needed
    fullText[0] = '\0';
    
    // Add question
    strncat(fullText, question.text, sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, "                    ", sizeof(fullText) - strlen(fullText) - 1); // Add padding/separator               ", sizeof(fullText) - strlen(fullText) - 1);
    
    // Add answers
    strncat(fullText, "A) ", sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, question.answers[0].text, sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, "                    ", sizeof(fullText) - strlen(fullText) - 1);
    
    strncat(fullText, "B) ", sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, question.answers[1].text, sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, "                    ", sizeof(fullText) - strlen(fullText) - 1);
    
    strncat(fullText, "C) ", sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, question.answers[2].text, sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, "                    ", sizeof(fullText) - strlen(fullText) - 1);
    
    strncat(fullText, "D) ", sizeof(fullText) - strlen(fullText) - 1);
    strncat(fullText, question.answers[3].text, sizeof(fullText) - strlen(fullText) - 1);
    
    // Now convert to pages
    int pageCount = 0;
    const char** allPages = hw.lcd.CreatePagesFromText(fullText, &pageCount);

    // Show on LCD
    gameStatus = GameStatus::ANSWERING;
    hw.lcd.SetPages(allPages, pageCount);
}

void QuestionGame::HandleArrowButtons() {
    if(gameStatus != GameStatus::ANSWERING) return;

    bool isRightPressed = hw.buttonRight.GetState();
    bool isLeftPressed = hw.buttonLeft.GetState();

    if(!isRightPressed && !isLeftPressed) return;

    hw.lcd.MovePage(isRightPressed);
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