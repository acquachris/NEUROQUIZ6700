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

    int totalPageCount = 0;
    int tempPageCount = 0;
    
    // Static array to hold all page pointers
    static const char* allPages[50];
    
    // Temporary buffers for each answer with prefix
    static char answerA[256];
    static char answerB[256];
    static char answerC[256];
    static char answerD[256];
    
    // Build answer strings with A), B), C), D) prefixes
    snprintf(answerA, sizeof(answerA), "A) %s", question.answers[0].text);
    snprintf(answerB, sizeof(answerB), "B) %s", question.answers[1].text);
    snprintf(answerC, sizeof(answerC), "C) %s", question.answers[2].text);
    snprintf(answerD, sizeof(answerD), "D) %s", question.answers[3].text);
    
    // --- Step 1: Get question pages ---
    tempPageCount = 0;
    const char** questionPages = hw.lcd.CreatePagesFromText(question.text, &tempPageCount);
    for (int i = 0; i < tempPageCount && totalPageCount < 50; i++) {
        allPages[totalPageCount++] = questionPages[i];
    }
    
    // --- Step 2: Add answer A (each answer on separate pages) ---
    tempPageCount = 0;
    const char** aAnswerPages = hw.lcd.CreatePagesFromText(answerA, &tempPageCount);
    for (int i = 0; i < tempPageCount && totalPageCount < 50; i++) {
        allPages[totalPageCount++] = aAnswerPages[i];
    }
    
    // --- Step 3: Add answer B ---
    tempPageCount = 0;
    const char** bAnswerPages = hw.lcd.CreatePagesFromText(answerB, &tempPageCount);
    for (int i = 0; i < tempPageCount && totalPageCount < 50; i++) {
        allPages[totalPageCount++] = bAnswerPages[i];
    }
    
    // --- Step 4: Add answer C ---
    tempPageCount = 0;
    const char** cAnswerPages = hw.lcd.CreatePagesFromText(answerC, &tempPageCount);
    for (int i = 0; i < tempPageCount && totalPageCount < 50; i++) {
        allPages[totalPageCount++] = cAnswerPages[i];
    }
    
    // --- Step 5: Add answer D ---
    tempPageCount = 0;
    const char** dAnswerPages = hw.lcd.CreatePagesFromText(answerD, &tempPageCount);
    for (int i = 0; i < tempPageCount && totalPageCount < 50; i++) {
        allPages[totalPageCount++] = dAnswerPages[i];
    }

    // Show on LCD
    gameStatus = GameStatus::ANSWERING;
    hw.lcd.SetPages(allPages, totalPageCount);
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