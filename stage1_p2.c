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
void parseFitnessData(char *line, int memberIndex);

void mainMenu() {
    char input[10];
    while (1) {
        printf("\n--- Magrathea Main Menu ---\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter your choice (I/II/III) or Q to quit: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "0") == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;
        else if (strcmp(input, "I") == 0 || strcmp(input, "i") == 0)
            audition();
        else if (strcmp(input, "II") == 0 || strcmp(input, "ii") == 0)
            training();
        else if (strcmp(input, "III") == 0 || strcmp(input, "iii") == 0)
            printf("Debut function not implemented yet.\n");
    }
}

void audition() {
    printf("Audition management selected.\n");
}

void training() {
    char input[10];
    while (1) {
        printf("\n--- Training Menu ---\n");
        printf("1. Physical Strength & Knowledge\n");
        printf("2. Self-Management & Teamwork\n");
        printf("3. Language & Pronunciation\n");
        printf("4. Vocal\n");
        printf("5. Dance\n");
        printf("6. Visual & Image\n");
        printf("7. Acting & Stage Performance\n");
        printf("8. Fan Communication\n");
        printf("Enter training stage number or Q to return: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

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
            printf("\n-- Physical Strength & Knowledge --\n");
            printf("A. Enter Fitness Data\n");
            printf("B. View Fitness Data\n");
            printf("C. Set Basic Workout Routine\n");
            printf("D. View Basic Workout Routine\n");
            printf("Enter your choice (A-D) or any other key to go back: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

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
            printf("You must pass stages 1 and 2 before accessing stage %d.\n", stage);
            return;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            printf("Did you complete the training and pass the certification? (Y for pass / N for fail): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            training_results[0][stage - 1] = (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) ? 'P' : 'F';
            printf("Result recorded: %c\n", training_results[0][stage - 1]);
        }
    }
}

void parseFitnessData(char *line, int memberIndex) {
    const char *categories[7] = {
        "1-Mile Run (min)", "Sprint 100m (s)", "30 Push-ups (min)",
        "50 Squats (min)", "50 Push-ups (min)", "Swim 400m (min)", "Weightlifting (xBW)"
    };

    char *token = strtok(line, ",");
    int count = 0;

    while (token != NULL && count < 7) {
        double val = atof(token);
        if (val <= 0) {
            printf("Invalid value for %s: %s\n", categories[count], token);
            return;
        }
        strncpy(health_scores[memberIndex][count], token, 29);
        health_scores[memberIndex][count][29] = '\0';
        token = strtok(NULL, ",");
        count++;
    }

    if (count != 7) {
        printf("Error: You must enter exactly 7 values.\n");
    } else {
        printf("Fitness data saved for %s.\n", milliways_members[memberIndex][1]);
    }
}

void setHealth() {
    char line[256];
    char input[50];
    int i;

    printf("\n--- Set Fitness Data ---\n");
    for (i = 0; i < MAX_MEMBERS; i++) {
        printf("%s (%s)\n", milliways_members[i][0], milliways_members[i][1]);
    }

    printf("Enter nickname of the member to input data: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    for (i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            printf("Enter 7 comma-separated test values for %s:\n", milliways_members[i][0]);
            printf("1-Mile Run (min), Sprint 100m (s), 30 Push-ups (min), 50 Squats (min), 50 Push-ups (min), Swim 400m (min), Weightlifting (xBW):\n");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0;
            parseFitnessData(line, i);
            return;
        }
    }

    printf("Member not found.\n");
}

void getHealth() {
    printf("\n--- Fitness Data ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%s (%s): ", milliways_members[i][0], milliways_members[i][1]);
        for (int j = 0; j < 7; j++) {
            if (strlen(health_scores[i][j]) > 0) {
                printf("%s", health_scores[i][j]);
                if (j < 6) printf(", ");
            }
        }
        printf("\n");
    }
}

void setExerciseRoutine() {
    char input[50];
    int memberIndex = -1;

    printf("\n--- Set Basic Workout Routine ---\n");
    printf("Available members:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%s (%s)\n", milliways_members[i][0], milliways_members[i][1]);
    }

    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\n");
        return;
    }

    for (int d = 0; d < DAYS; d++) {
        printf("\n%s:\n", day_names[d]);
        for (int e = 0; e < 2; e++) {
            printf("Select type for Exercise %d (0-4): ", e + 1);
            fgets(input, sizeof(input), stdin);
            int typeIndex = atoi(input);
            if (typeIndex < 0 || typeIndex >= EXERCISES) {
                printf("Invalid exercise type. Skipping.\n");
                continue;
            }

            printf("Select exercise (0 or 1): ");
            fgets(input, sizeof(input), stdin);
            int exerciseIndex = atoi(input);
            if (exerciseIndex < 0 || exerciseIndex > 1 || strlen(exercise_types[typeIndex][exerciseIndex]) == 0) {
                printf("Invalid selection. Skipping.\n");
                continue;
            }
            strncpy(member_routine[memberIndex][d][e], exercise_types[typeIndex][exerciseIndex], 29);
        }
    }
    printf("Workout routine saved for %s.\n", milliways_members[memberIndex][1]);
}

void getExerciseRoutine() {
    char input[50];
    int memberIndex = -1;

    printf("\n--- View Basic Workout Routine ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%s (%s)\n", milliways_members[i][0], milliways_members[i][1]);
    }

    printf("Enter member nickname: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\n");
        return;
    }

    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s, %s\n", day_names[d], member_routine[memberIndex][d][0], member_routine[memberIndex][d][1]);
    }
}

int main() {
    mainMenu();
    return 0;
}
