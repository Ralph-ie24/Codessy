#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5
#define TESTS 7

// Member Info [Name][Nickname]
char *milliways_members[MAX_MEMBERS][2] = {
    {"Zaphod Beeblebrox", "Zaphod"},
    {"Trillian Astra", "Trillian"},
    {"Ford Prefect", "Ford"},
    {"Arthur Dent", "Arthur"},
    {"Marvin", "Marvin"}
};

// Fitness Test Categories
char *test_names[TESTS] = {
    "1-Mile Run (min)",
    "Speed Sprint (sec)",
    "Push-ups (min)",
    "Squats (min)",
    "Arm Strength (min)",
    "Swimming (min)",
    "Weightlifting (x BW)"
};

// Health scores: [memberIndex * TESTS + testIndex]
float health_scores[MAX_MEMBERS * TESTS] = {0};

// Training results for 8 stages: 'P', 'F', or '-'
char trainingResults[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

// Function declarations
void auditionManagement();
void debut();
void training();
void trainingStage(int stageIndex);
int isTrainingUnlocked(int stageIndex);
int hasPassed(int stageIndex);
void setHealth();
void getHealth();
void parseFitnessData(char *line, int memberIndex);

int main() {
    char choice[10];

    while (1) {
        printf("\n=== Magrathea Main Menu ===\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter your choice (I/II/III) or 0/Q/q to quit: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;

        if (strcmp(choice, "0") == 0 || strcasecmp(choice, "q") == 0 || strlen(choice) == 0) {
            printf("Exiting the program...\n");
            break;
        } else if (strcmp(choice, "I") == 0) {
            auditionManagement();
        } else if (strcmp(choice, "II") == 0) {
            training();
        } else if (strcmp(choice, "III") == 0) {
            debut();
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void auditionManagement() {
    printf("\n[Audition Management selected.]\n");
}

void debut() {
    printf("\n[Debut selected.]\n");
}

void training() {
    char input[10];
    int stage;

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < 8; i++) {
            printf("%d. ", i + 1);
            switch (i) {
                case 0: printf("Physical Strength & Knowledge"); break;
                case 1: printf("Self-Management & Teamwork"); break;
                case 2: printf("Language & Pronunciation"); break;
                case 3: printf("Vocal"); break;
                case 4: printf("Dance"); break;
                case 5: printf("Visual & Image"); break;
                case 6: printf("Acting & Stage Performance"); break;
                case 7: printf("Fan Communication"); break;
            }
            printf(" [%c]\n", trainingResults[i]);
        }

        printf("Enter stage number (1-8), or 0/Q/q to return: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "0") == 0 || strcasecmp(input, "q") == 0 || strlen(input) == 0) {
            printf("Returning to Main Menu...\n");
            break;
        }

        stage = atoi(input);
        if (stage >= 1 && stage <= 8) {
            if (stage == 1) {
                printf("  A. Enter Fitness Data\n");
                printf("  B. View Fitness Data\n");
                printf("  Enter your choice (A/B) or any other key to proceed to evaluation: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                if (strcasecmp(input, "A") == 0) {
                    setHealth();
                } else if (strcasecmp(input, "B") == 0) {
                    getHealth();
                } else {
                    trainingStage(stage - 1);
                }
            } else {
                trainingStage(stage - 1);
            }
        } else {
            printf("Invalid stage. Try again.\n");
        }
    }
}

void trainingStage(int stageIndex) {
    char response[10];

    if (trainingResults[stageIndex] != '-') {
        printf("You have already completed this stage.\n");
        return;
    }

    if (!isTrainingUnlocked(stageIndex)) {
        if (!hasPassed(0) && !hasPassed(1)) {
            printf("*** You cannot select this option because you have not passed Stages 1 and 2. ***\n");
        } else if (!hasPassed(0)) {
            printf("*** You cannot select this option because you have not passed Stage 1. ***\n");
        } else if (!hasPassed(1)) {
            printf("*** You cannot select this option because you have not passed Stage 2. ***\n");
        }
        return;
    }

    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = 0;

    if (strcasecmp(response, "Y") == 0) {
        printf("Did you complete the training and pass the certification? (Y = Pass, N = Fail): ");
        fgets(response, sizeof(response), stdin);
        response[strcspn(response, "\n")] = 0;

        if (strcasecmp(response, "Y") == 0) {
            trainingResults[stageIndex] = 'P';
            printf("Stage %d marked as Passed.\n", stageIndex + 1);
        } else {
            trainingResults[stageIndex] = 'F';
            printf("Stage %d marked as Failed.\n", stageIndex + 1);
        }
    } else {
        printf("Returning to Training Menu.\n");
    }
}

int isTrainingUnlocked(int stageIndex) {
    if (stageIndex < 2) return 1;
    return hasPassed(0) && hasPassed(1);
}

int hasPassed(int stageIndex) {
    return trainingResults[stageIndex] == 'P';
}

void setHealth() {
    char line[256];

    printf("\n--- Enter Fitness Data for Milliways Members ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter 7 comma-separated test values for %s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
        printf("Order: 1-Mile, Sprint, Push-ups, Squats, Arm Strength, Swimming, Weightlifting\n> ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;
        parseFitnessData(line, i);
    }
    printf("All fitness data recorded successfully.\n");
}

void parseFitnessData(char *line, int memberIndex) {
    char *token = strtok(line, ",");
    int i = 0;

    while (token != NULL && i < TESTS) {
        health_scores[memberIndex * TESTS + i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }

    if (i < TESTS) {
        printf("Warning: Incomplete data for %s.\n", milliways_members[memberIndex][1]);
    }
}

void getHealth() {
    char input[50];
    int i, j;

    printf("\n--- View Fitness Data ---\n");
    printf("1. View all members' fitness data\n");
    printf("2. View data for a specific member\n");
    printf("3. View specific test for a member\n");
    printf("Enter your choice (1/2/3): ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == '1') {
        for (i = 0; i < MAX_MEMBERS; i++) {
            printf("\n%s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
            for (j = 0; j < TESTS; j++) {
                printf("%s: %.2f\n", test_names[j], health_scores[i * TESTS + j]);
            }
        }
    } else if (input[0] == '2' || input[0] == '3') {
        printf("Enter nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        for (i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, milliways_members[i][1]) == 0) {
                if (input[0] == '2') {
                    printf("\n%s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
                    for (j = 0; j < TESTS; j++) {
                        printf("%s: %.2f\n", test_names[j], health_scores[i * TESTS + j]);
                    }
                } else {
                    printf("Choose test number (1-7):\n");
                    for (j = 0; j < TESTS; j++) {
                        printf("%d. %s\n", j + 1, test_names[j]);
                    }
                    fgets(input, sizeof(input), stdin);
                    int testIndex = atoi(input) - 1;

                    if (testIndex >= 0 && testIndex < TESTS) {
                        printf("%s's %s score: %.2f\n", milliways_members[i][1], test_names[testIndex], health_scores[i * TESTS + testIndex]);
                    } else {
                        printf("Invalid test number.\n");
                    }
                }
                return;
            }
        }
        printf("Member not found.\n");
    } else {
        printf("Invalid selection.\n");
    }
}
