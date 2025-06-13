#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRAINEES 4
#define MAX_MENTORS 8

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

int trainee_list[MAX_TRAINEES][2]; // [0] = nickname ASCII sum, [1] = ability score
Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; i < strlen(nickname); i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100; // Random value between 100 and 1000
}

void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainee_list[i][0] = parseIntMember(trainees[i][1]);
        trainee_list[i][1] = getRandomAbility();
    }
    printf("Trainee data initialized.\\n");
}

void inputMentors() {
    printf("\\n-- Mentor Input (Max 8) --\\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("Enter mentor name for ID %d: ", mentors[i].id);
        fgets(mentors[i].name, sizeof(mentors[i].name), stdin);
        mentors[i].name[strcspn(mentors[i].name, "\\n")] = 0;
        mentors[i].mentee_number = -1;
        mentor_count++;
    }
}

void matchMentoring() {
    initializeTrainees();
    inputMentors();

    printf("\\n-- Mentor Matching Results --\\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int match_id = i % MAX_MENTORS;
        mentors[match_id].mentee_number = i;
        printf("Trainee %d (ASCII Sum: %d, Ability: %d) matched with Mentor ID %d (%s)\\n",
               i + 1, trainee_list[i][0], trainee_list[i][1],
               mentors[match_id].id, mentors[match_id].name);
    }
}

void mentoringMenu() {
    char input[10];
    while (1) {
        printf("\\n--- Self-Management & Teamwork Menu ---\\n");
        printf("A. Mentoring\\n");
        printf("Enter your choice or Q to go back: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
            break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0)
            matchMentoring();
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator
    mentoringMenu();
    return 0;
}