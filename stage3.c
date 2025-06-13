#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // sleep()

#define TOTAL_QUESTIONS 10
#define QUIZ_QUESTIONS 5
#define MAX_TRAINEES 4

//----------------------------------------//
// Struct Definitions
//----------------------------------------//

typedef struct {
    int id;
    char question[100];
    char answer[100];
} KoreanQuestion;

typedef struct {
    char name[30];
    char nickname[20];
    char nationality[20];
    int score;
    char pass[10];
} MilliewaysTrainee;

typedef struct {
    int question_id;
    char correctness;  // 'O' or 'X'
} QuizAnswer;

//----------------------------------------//
// Global Data
//----------------------------------------//

KoreanQuestion questionBank[TOTAL_QUESTIONS] = {
    {1, "What is '사랑' in English?", "love"},
    {2, "What is '학교' in English?", "school"},
    {3, "What is '책' in English?", "book"},
    {4, "What is '물' in English?", "water"},
    {5, "What is '음식' in English?", "food"},
    {6, "What is '친구' in English?", "friend"},
    {7, "What is '하늘' in English?", "sky"},
    {8, "What is '행복' in English?", "happiness"},
    {9, "What is '바다' in English?", "sea"},
    {10, "What is '평화' in English?", "peace"}
};

MilliewaysTrainee trainees[MAX_TRAINEES] = {
    {"Park Ji-yeon", "Ariel", "Korea", 0, "None"},
    {"Ethan Smith", "Simba", "USA", 0, "None"},
    {"Helena Silva", "Belle", "Brazil", 0, "None"},
    {"Liam Wilson", "Aladdin", "UK", 0, "None"}
};

QuizAnswer quizSheet[QUIZ_QUESTIONS];

//----------------------------------------//
// Utility Functions
//----------------------------------------//

int isAlreadySelected(int selected[], int count, int candidate) {
    for (int i = 0; i < count; i++) {
        if (selected[i] == candidate) return 1;
    }
    return 0;
}

MilliewaysTrainee* selectRandomTaker() {
    int eligible[MAX_TRAINEES];
    int eligible_count = 0;

    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(trainees[i].nationality, "Korea") != 0) {
            eligible[eligible_count++] = i;
        }
    }

    if (eligible_count == 0) {
        printf("No eligible trainees available.\n");
        return NULL;
    }

    int idx = eligible[rand() % eligible_count];
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[idx].name);
    return &trainees[idx];
}

int checkAnswer(int question_id, char *userAnswer) {
    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        if (questionBank[i].id == question_id) {
            return strcmp(questionBank[i].answer, userAnswer) == 0;
        }
    }
    return 0;
}

void displayQuizResult(MilliewaysTrainee* trainee) {
    printf("\n===== Quiz Results =====\n");
    for (int i = 0; i < QUIZ_QUESTIONS; i++) {
        printf("Q%d (ID:%d): %c\n", i + 1, quizSheet[i].question_id, quizSheet[i].correctness);
    }
    printf("Total Score: %d\n", trainee->score);
    printf("Status: %s\n", trainee->pass);
}

void runQuiz(MilliewaysTrainee* trainee) {
    int selected[QUIZ_QUESTIONS];
    int count = 0, score = 0;

    printf("The quiz will begin in 30 seconds. Please wait...\n");
    sleep(2);  // for testing, replace with sleep(30) for real timing

    while (count < QUIZ_QUESTIONS) {
        int q_index = rand() % TOTAL_QUESTIONS;
        if (!isAlreadySelected(selected, count, q_index)) {
            selected[count] = q_index;
            KoreanQuestion *q = &questionBank[q_index];

            printf("Q%d: %s ", count + 1, q->question);
            char userInput[100];
            fgets(userInput, sizeof(userInput), stdin);
            userInput[strcspn(userInput, "\n")] = 0;

            if (checkAnswer(q->id, userInput)) {
                printf("Correct!\n");
                score += 20;
                quizSheet[count].correctness = 'O';
            } else {
                printf("Incorrect. Correct answer: %s\n", q->answer);
                quizSheet[count].correctness = 'X';
            }
            quizSheet[count].question_id = q->id;
            count++;
        }
    }

    trainee->score = score;
    strcpy(trainee->pass, (score >= 80) ? "Pass" : "Fail");

    displayQuizResult(trainee);
}

void testKoreanLanguage() {
    MilliewaysTrainee *taker = selectRandomTaker();
    if (taker != NULL) {
        runQuiz(taker);
    }
}

void showAllResults() {
    printf("\n--- Millieways Trainee Results ---\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        printf("%s (%s) | Nationality: %s | Score: %d | Status: %s\n",
               trainees[i].name, trainees[i].nickname, trainees[i].nationality,
               trainees[i].score, trainees[i].pass);
    }
}

//----------------------------------------//
// Menus
//----------------------------------------//

void languageMenu() {
    char input[10];
    while (1) {
        printf("\n--- Language and Pronunciation Training ---\n");
        printf("A. Korean Quiz\n");
        printf("B. View Results\n");
        printf("Q. Return\n");
        printf("Enter option: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0) testKoreanLanguage();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0) showAllResults();
        else printf("Invalid input.\n");
    }
}

void mainMenu() {
    char input[10];
    while (1) {
        printf("\n===== Millieways Stage 3 =====\n");
        printf("II. Training\n");
        printf("3. Language and Pronunciation Training\n");
        printf("Q. Exit Program\n");
        printf("Select menu: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) break;
        else if (strcmp(input, "3") == 0) languageMenu();
        else printf("Invalid selection.\n");
    }
}

int main() {
    srand(time(NULL));
    mainMenu();
    return 0;
}