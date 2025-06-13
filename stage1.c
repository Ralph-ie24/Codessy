#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variable to persist training results
char trainingResults[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

// Function declarations
void auditionManagement();
void training();
void debut();

void trainingStage(int stageIndex);
int isTrainingUnlocked(int stageIndex);
int hasPassed(int stageIndex);
int isNumeric(const char *s);

int main() {
    char choice[10];

    while (1) {
        printf("=====================\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("=====================\n");
        printf("Select a menu option (Exit: Empty input, 0, Q, q): ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;

        if (strcmp(choice, "0") == 0 || strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0 || strlen(choice) == 0) {
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
        printf("####################\n");
        printf(" Training Management\n");
        printf("####################\n");

        for (int i = 0; i < 8; i++) {
            printf("%d. ", i + 1);
            switch(i) {
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

        printf("--------------------\n");
        printf("Select a training menu (Go to main menu: m, M): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0 || strlen(input) == 0 ||
            strcmp(input, "m") == 0 || strcmp(input, "M") == 0) {
            printf("Returning to Main Menu...\n");
            break;
        }

        if (!isNumeric(input)) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        stage = atoi(input);
        if (stage >= 1 && stage <= 8) {
            trainingStage(stage - 1);
        } else {
            printf("Invalid stage. Try again.\n");
        }
    }
}

void trainingStage(int stageIndex) {
    char response[10];

    if (trainingResults[stageIndex] != '-') {
        printf("You have already completed this stage. Cannot re-select.\n");
        return;
    }

    if (!isTrainingUnlocked(stageIndex)) {
        if (!hasPassed(0)) {
            printf("*** You cannot select this option because you have not completed stage 1. ***\n");
        } else if (!hasPassed(1)) {
            printf("*** You cannot select this option because you have not completed stages 1 and 2. ***\n");
        }
        return;
    }

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = 0;

    if (strcmp(response, "Y") == 0 || strcmp(response, "y") == 0) {
        printf("Did you complete the training and pass the certification? (Y = Pass, N = Fail): ");
        fgets(response, sizeof(response), stdin);
        response[strcspn(response, "\n")] = 0;

        if (strcmp(response, "Y") == 0 || strcmp(response, "y") == 0) {
            trainingResults[stageIndex] = 'P';
            printf("Stage %d marked as Passed.\n", stageIndex + 1);
        } else {
            trainingResults[stageIndex] = 'F';
            printf("Stage %d marked as Failed.\n", stageIndex + 1);
        }
    } else {
        printf("Returning to Training Menu.\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int isTrainingUnlocked(int stageIndex) {
    if (stageIndex < 2) return 1;
    return hasPassed(0) && hasPassed(1);
}

int hasPassed(int stageIndex) {
    return trainingResults[stageIndex] == 'P';
}

int isNumeric(const char *s) {
    if (*s == '\0') return 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return 1;
}