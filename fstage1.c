#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 4
#define DAYS 6
#define EXERCISES 5

char *milliways_members[MAX_MEMBERS][2] = {
    {"Park Ji-yeon", "Ariel"},
    {"Ethan Smith", "Simba"},
    {"Helena Silva", "Belle"},
    {"Liam Wilson", "Aladdin"},
};

char *exercise_types[EXERCISES][3] = {
    {"Running", "Cycling", "Fast Walking"},
    {"Push-ups", "Squats", ""},
    {"Leg Press", "Leg Curl", ""},
    {"Pull-ups", "Chin-ups", ""},
    {"Plank", "Crunches", ""}
};

char *day_names[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char training_results[MAX_MEMBERS][8] = {{0}};
char health_scores[MAX_MEMBERS][8][30];
char member_routine[MAX_MEMBERS][DAYS][2][30];

void audition();
void training();
void trainingStage(int stage);
void setHealth();
void getHealth();
void setExerciseRoutine();
void getExerciseRoutine();

void mainMenu() {
    char input[10];
    while (1) {
        printf("\\n--- Magrathea Main Menu ---\\n");
        printf("I. Audition Management\\n");
        printf("II. Training\\n");
        printf("III. Debut\\n");
        printf("Enter your choice (I/II/III) or Q to quit: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;
        else if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0)
            audition();
        else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0)
            training();
        else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0)
            printf("Debut function not implemented yet.\\n");
    }
}

void audition() {
    printf("Audition management selected.\\n");
}

void training() {
    char input[10];
    while (1) {
        printf("\\n--- Training Menu ---\\n");
        printf("1. Physical Strength & Knowledge\\n");
        printf("2. Self-Management & Teamwork\\n");
        printf("3. Language & Pronunciation\\n");
        printf("4. Vocal\\n");
        printf("5. Dance\\n");
        printf("6. Visual & Image\\n");
        printf("7. Acting & Stage Performance\\n");
        printf("8. Fan Communication\\n");
        printf("Enter training stage number or Q to return: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;

        int stage = atoi(input);
        if (stage >= 1 && stage <= 8)
            trainingStage(stage);
    }
}

void trainingStage(int stage) {
    char input[10];
    if (stage == 1) {
        while (1) {
            printf("\\n-- Physical Strength & Knowledge --\\n");
            printf("A. Enter Fitness Data\\n");
            printf("B. View Fitness Data\\n");
            printf("C. Set Basic Workout Routine\\n");
            printf("D. View Basic Workout Routine\\n");
            printf("Enter your choice (A-D) or any other key to go back: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\\n")] = 0;

            if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0)
                setHealth();
            else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0)
                getHealth();
            else if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0)
                setExerciseRoutine();
            else if (strcmp(input, "D") == 0 || strcmp(input, "d") == 0)
                getExerciseRoutine();
            else
                break;
        }
    } else {
        if ((stage > 2) && (training_results[0][0] != 'P' || training_results[0][1] != 'P')) {
            printf("You must pass stages 1 and 2 before accessing stage %d.\\n", stage);
            return;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\\n")] = 0;

        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            printf("Did you complete the training and pass the certification? (Y for pass / N for fail): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\\n")] = 0;
            training_results[0][stage - 1] = (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) ? 'P' : 'F';
            printf("Result recorded: %c\\n", training_results[0][stage - 1]);
        }
    }
}

void setHealth() {
    char input[100];
    int memberIndex = -1;

    printf("\\n--- Enter Fitness Data ---\\n");
    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_members[i][1], input) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\\n");
        return;
    }

    printf("Enter 7 test results (comma-separated):\\n");
    printf("1-Mile Run (min), Sprint 100m (s), 30 Push-ups (min), 50 Squats (min), 50 Push-ups (min), Swim 400m (min), Weightlifting (xBW):\\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\\n")] = 0;

    char *token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < 7) {
        strncpy(health_scores[memberIndex][i], token, 29);
        health_scores[memberIndex][i][29] = '\\0';
        token = strtok(NULL, ",");
        i++;
    }

    printf("Fitness data saved for %s\\n", milliways_members[memberIndex][1]);
}

void getHealth() {
    char input[50];
    int memberIndex = -1;

    printf("\\n--- View Fitness Data ---\\n");
    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\\n");
        return;
    }

    printf("Fitness Data for %s:\\n", milliways_members[memberIndex][1]);
    char *categories[7] = {
        "1-Mile Run", "Sprint 100m", "30 Push-ups", "50 Squats",
        "50 Push-ups", "Swim 400m", "Weightlifting (xBW)"
    };

    for (int i = 0; i < 7; i++) {
        printf("%s: %s\\n", categories[i], health_scores[memberIndex][i]);
    }
}

void setExerciseRoutine() {
    char input[50];
    int memberIndex = -1;

    printf("\\n--- Set Basic Workout Routine ---\\n");
    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\\n");
        return;
    }

    int core_used = 0;

    for (int d = 0; d < DAYS; d++) {
        printf("\\n--- %s ---\\n", day_names[d]);

        printf("Select a cardio exercise (1. Running, 2. Cycling, 3. Fast Walking): ");
        fgets(input, sizeof(input), stdin);
        int c = atoi(input);
        if (c < 1 || c > 3) continue;
        strcpy(member_routine[memberIndex][d][0], exercise_types[0][c - 1]);

        printf("Select strength/core type:\\n1. Full-body\\n2. Lower-body\\n3. Upper-body\\n4. Core\\n> ");
        fgets(input, sizeof(input), stdin);
        int type = atoi(input);

        if (type == 4 && core_used) {
            printf("Core exercise already used this week. Choose again.\\n");
            d--;
            continue;
        }

        int sub = 0;
        while (strlen(exercise_types[type][sub]) > 0) {
            printf("%d. %s\\n", sub + 1, exercise_types[type][sub]);
            sub++;
        }

        fgets(input, sizeof(input), stdin);
        int ex = atoi(input);
        if (ex < 1 || ex > sub) continue;

        strcpy(member_routine[memberIndex][d][1], exercise_types[type][ex - 1]);
        if (type == 4) core_used = 1;
    }

    printf("Routine set for %s.\\n", milliways_members[memberIndex][1]);
}

void getExerciseRoutine() {
    char input[50];
    int memberIndex = -1;

    printf("\\n--- View Workout Routine ---\\n");
    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\\n");
        return;
    }

    printf("Workout Routine for %s:\\n", milliways_members[memberIndex][1]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: Cardio - %s, Strength/Core - %s\\n", day_names[d],
               member_routine[memberIndex][d][0], member_routine[memberIndex][d][1]);
    }
}

int main() {
    mainMenu();
    return 0;
}