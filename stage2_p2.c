#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRAINEES 4
#define MAX_MENTORS 8
#define MAX_TRAUMA 10
#define MAX_COUNSELING 30

typedef struct {
    int id;
    char name[30];
    int mentee_number;
} Mentor;

char *trainees[MAX_TRAINEES][2] = {
    {"Park Ji-yeon", "Ariel"},
    {"Ethan Smith", "Simba"},
    {"Helena Silva", "Belle"},
    {"Liam Wilson", "Aladdin"},
};

int trainee_list[MAX_TRAINEES][2];
Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// Trauma & Counseling structures
typedef struct {
    char nickname[10];
    int age;
    char trauma[200];
} Trauma;

typedef struct {
    int id;
    char question[150];
} Question;

typedef struct {
    char nickname[10];
    char question[150];
    char response[101];
} Counseling;

Trauma traumas[MAX_TRAUMA];
int trauma_count = 0;
Counseling counseling_sessions[MAX_COUNSELING];
int counseling_count = 0;

const Question questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

// Helper functions
int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; i < strlen(nickname); i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100;
}

void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainee_list[i][0] = parseIntMember(trainees[i][1]);
        trainee_list[i][1] = getRandomAbility();
    }
    printf("Trainee data initialized.\n");
}

void inputMentors() {
    printf("\n-- Mentor Input (Max %d, enter Q to stop early) --\n", MAX_MENTORS);
    mentor_count = 0;
    for (int i = 0; i < MAX_MENTORS; i++) {
        char input[30];
        printf("Enter mentor name for ID %d (or Q to quit): ", i + 1);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;

        strncpy(mentors[mentor_count].name, input, sizeof(mentors[mentor_count].name));
        mentors[mentor_count].id = mentor_count + 1;
        mentors[mentor_count].mentee_number = -1;
        mentor_count++;
    }

    if (mentor_count < MAX_TRAINEES) {
        printf("Not enough mentors to match all trainees. At least %d required.\n", MAX_TRAINEES);
        mentor_count = 0;
    }
}

void matchMentoring() {
    initializeTrainees();
    inputMentors();

    if (mentor_count < MAX_TRAINEES) {
        printf("Mentoring aborted due to insufficient mentors.\n");
        return;
    }

    int used[MAX_MENTORS] = {0};
    printf("\n-- Mentor Matching Results --\n");

    for (int i = 0; i < MAX_TRAINEES; i++) {
        int match_id;
        do {
            match_id = rand() % mentor_count;
        } while (used[match_id]);
        used[match_id] = 1;

        mentors[match_id].mentee_number = i;
        printf("Trainee %d (%s, ASCII Sum: %d, Ability: %d) matched with Mentor ID %d (%s)\n",
               i + 1, trainees[i][1], trainee_list[i][0], trainee_list[i][1],
               mentors[match_id].id, mentors[match_id].name);
    }
}

// Trauma Functions
void inputTrauma() {
    char nickname[10], trauma[200];
    while (1) {
        printf("\nEnter member nickname (or Q to quit): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        if (strcmp(nickname, "Q") == 0 || strcmp(nickname, "q") == 0) break;

        int found = 0;
        for (int i = 0; i < MAX_TRAINEES; i++) {
            if (strcmp(trainees[i][1], nickname) == 0) {
                found = 1;
                printf("Enter trauma description for %s: ", nickname);
                fgets(trauma, sizeof(trauma), stdin);
                trauma[strcspn(trauma, "\n")] = 0;
                strncpy(traumas[trauma_count].nickname, nickname, sizeof(traumas[trauma_count].nickname));
                traumas[trauma_count].age = rand() % 10 + 18;
                strncpy(traumas[trauma_count].trauma, trauma, sizeof(traumas[trauma_count].trauma));
                trauma_count++;
                printf("Trauma data saved for %s.\n", nickname);
                break;
            }
        }
        if (!found)
            printf("Nickname not found. Please try again.\n");
    }
}

void counselingSession() {
    if (trauma_count == 0) {
        printf("No trauma data available.\n");
        return;
    }

    printf("\nMembers with trauma entries:\n");
    for (int i = 0; i < trauma_count; i++) {
        printf("%d. %s\n", i + 1, traumas[i].nickname);
    }

    int choice;
    printf("Select member by number: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > trauma_count) {
        printf("Invalid choice.\n");
        return;
    }

    Trauma selected = traumas[choice - 1];
    int q_indices[3];

    for (int i = 0; i < 3; i++) {
        int unique;
        do {
            unique = 1;
            q_indices[i] = rand() % 5;
            for (int j = 0; j < i; j++) {
                if (q_indices[i] == q_indices[j]) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
    }

    for (int i = 0; i < 3; i++) {
        char response[101];
        while (1) {
            printf("Q%d: %s\n> ", i + 1, questions[q_indices[i]].question);
            fgets(response, sizeof(response), stdin);
            response[strcspn(response, "\n")] = 0;
            if (strlen(response) == 0 || strlen(response) > 100) {
                printf("Response must be between 1 and 100 characters. Try again.\n");
            } else {
                strncpy(counseling_sessions[counseling_count].nickname, selected.nickname, sizeof(counseling_sessions[counseling_count].nickname));
                strncpy(counseling_sessions[counseling_count].question, questions[q_indices[i]].question, sizeof(counseling_sessions[counseling_count].question));
                strncpy(counseling_sessions[counseling_count].response, response, sizeof(counseling_sessions[counseling_count].response));
                counseling_count++;
                break;
            }
        }
    }

    printf("\nCounseling session completed for %s.\n", selected.nickname);
}

void viewCounselingData() {
    if (trauma_count == 0) {
        printf("No counseling data available.\n");
        return;
    }

    printf("\n--- Completed Counseling Sessions ---\n");
    for (int i = 0; i < trauma_count; i++) {
        printf("%d. %s\n", i + 1, traumas[i].nickname);
    }

    int choice;
    printf("Select member by number: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > trauma_count) {
        printf("Invalid choice.\n");
        return;
    }

    Trauma selected = traumas[choice - 1];
    printf("\nNickname: %s\nAge: %d\nTrauma: %s\n", selected.nickname, selected.age, selected.trauma);
    for (int i = 0; i < counseling_count; i++) {
        if (strcmp(counseling_sessions[i].nickname, selected.nickname) == 0) {
            printf("Q: %s\nA: %s\n", counseling_sessions[i].question, counseling_sessions[i].response);
        }
    }
}

void overcomeTrauma() {
    char input[10];
    while (1) {
        printf("\n-- Trauma Management Menu --\n");
        printf("A. Input Trauma\n");
        printf("B. Start Counseling\n");
        printf("C. View Counseling\n");
        printf("Q. Return to Previous Menu\n");
        printf("Select an option: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0)
            inputTrauma();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0)
            counselingSession();
        else if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0)
            viewCounselingData();
    }
}

void mentoringMenu() {
    char input[10];
    while (1) {
        printf("\n--- Self-Management & Teamwork Menu ---\n");
        printf("A. Mentoring\n");
        printf("B. Trauma Management\n");
        printf("Q. Exit Program\n");
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0)
            matchMentoring();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0)
            overcomeTrauma();
    }
}

int main() {
    srand(time(NULL));
    mentoringMenu();
    return 0;
}
