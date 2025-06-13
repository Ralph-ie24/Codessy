#include <stdio.h>
#include <string.h>

// Function declarations
void auditionManagement();
void training();
void debut();

void trainingStage(int stageIndex, char trainingResults[]);
int isTrainingUnlocked(int stageIndex, char trainingResults[]);
int hasPassed(int stageIndex, char trainingResults[]);

int main() {
    char choice[10];

    while (1) {
        printf("\n=== Magrathea Main Menu ===\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter your choice (I/II/III) or 0/Q/q to quit: ");
        fgets(choice, sizeof(choice), stdin);

        // Trim newline character
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

// Audition Management placeholder
void auditionManagement() {
    printf("\n[Audition Management selected.]\n");
}

// Debut placeholder
void debut() {
    printf("\n[Debut selected.]\n");
}

// Training menu
void training() {
    char trainingResults[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};
    char input[10];
    int stage;

    while (1) {
        printf("\n=== Training Menu ===\n");
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

        printf("Enter stage number to evaluate (1-8), or 0/Q/q to return to Main Menu: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0 || strlen(input) == 0) {
            printf("Returning to Main Menu...\n");
            break;
        }

        stage = atoi(input);
        if (stage >= 1 && stage <= 8) {
            trainingStage(stage - 1, trainingResults);
        } else {
            printf("Invalid stage. Try again.\n");
        }
    }
}

// Handles evaluation for one training stage
void trainingStage(int stageIndex, char trainingResults[]) {
    char response[10];

    if (trainingResults[stageIndex] != '-') {
        printf("You have already completed this stage. Cannot re-select.\n");
        return;
    }

    if (!isTrainingUnlocked(stageIndex, trainingResults)) {
        printf("You must pass Stages 1 and 2 before accessing this stage.\n");
        return;
    }

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
}

// Returns 1 if stage is allowed to be taken
int isTrainingUnlocked(int stageIndex, char trainingResults[]) {
    if (stageIndex < 2) return 1;
    return hasPassed(0, trainingResults) && hasPassed(1, trainingResults);
}

// Checks if the stage has been passed
int hasPassed(int stageIndex, char trainingResults[]) {
    return trainingResults[stageIndex] == 'P';
}
