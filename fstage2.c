#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// === Configuration Constants ===
#define MAX_TRAINEES 4
#define MAX_MENTORS 8
#define MAX_TRAUMA 10
#define MAX_COUNSELING 30

// === Data Structures ===

typedef struct {
    int id;
    char name[30];
    int mentee_number;
} Mentor;

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

typedef struct {
    char keyword[8];
    char message[512];
} ArthurEgg;

// === Global Variables ===

// Trainee Data
char *trainees[MAX_TRAINEES][2] = {
    {"Park Ji-yeon", "Ariel"},
    {"Ethan Smith", "Simba"},
    {"Helena Silva", "Belle"},
    {"Liam Wilson", "Aladdin"},
};

int trainee_list[MAX_TRAINEES][2];
Mentor mentors[MAX_MENTORS];
int mentor_count = 0;

// Trauma & Counseling
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

// Arthur Easter Egg Data
ArthurEgg arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

// === Utility Functions ===

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

// === Mentoring Functions ===

void inputMentors() {
    printf("\n-- Mentor Input (Max 8) --\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("Enter mentor name for ID %d: ", mentors[i].id);
        fgets(mentors[i].name, sizeof(mentors[i].name), stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = 0;
        mentors[i].mentee_number = -1;
        mentor_count++;
    }
}

void matchMentoring() {
    initializeTrainees();
    inputMentors();

    printf("\n-- Mentor Matching Results --\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int match_id = i % MAX_MENTORS;
        mentors[match_id].mentee_number = i;
        printf("Trainee %d (ASCII Sum: %d, Ability: %d) matched with Mentor ID %d (%s)\n",
               i + 1, trainee_list[i][0], trainee_list[i][1],
               mentors[match_id].id, mentors[match_id].name);
    }
}

// === Trauma Management Functions ===

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
                strcpy(traumas[trauma_count].nickname, nickname);
                traumas[trauma_count].age = (rand() % 10) + 18;
                strcpy(traumas[trauma_count].trauma, trauma);
                trauma_count++;
                break;
            }
        }
        found ? printf("Trauma data saved for %s.\n", nickname) : printf("Nickname not found. Please try again.\n");
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
        int unique = 0;
        while (!unique) {
            q_indices[i] = rand() % 5;
            unique = 1;
            for (int j = 0; j < i; j++) {
                if (q_indices[i] == q_indices[j]) {
                    unique = 0;
                    break;
                }
            }
        }
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
                strcpy(counseling_sessions[counseling_count].nickname, selected.nickname);
                strcpy(counseling_sessions[counseling_count].question, questions[q_indices[i]].question);
                strcpy(counseling_sessions[counseling_count].response, response);
                counseling_count++;
                break;
            }
        }
    }

    printf("\nCounseling session completed for %s.\n", selected.nickname);
}

void viewCounselingData() {
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

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0) inputTrauma();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0) counselingSession();
        else if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0) viewCounselingData();
        else printf("Invalid input.\n");
    }
}

// === Arthur Easter Egg Functions ===

int isRightChar(char user_input, int reversed_binary) {
    return (int)user_input == reversed_binary;
}

int isEasterEgg(char user_word[]) {
    return strcmp(user_word, arthur.keyword) == 0;
}

void find_easter_egg() {
    printf("\n<<Arthur's Easter Egg>>\n");
    int binaries[7];

    for (int i = 0; i < 7; i++) {
        unsigned char ch = arthur.keyword[i];
        unsigned char reversed = 0;
        for (int b = 0; b < 8; b++) {
            reversed <<= 1;
            reversed |= (ch >> b) & 1;
        }
        binaries[i] = reversed;
        printf("Reversed Binary %d: %08b\n", i + 1, reversed);
    }

    char user_chars[8];
    for (int i = 0; i < 7; i++) {
        while (1) {
            char input_char;
            printf("Enter character for Binary %d: ", i + 1);
            scanf(" %c", &input_char);
            if (isRightChar(input_char, binaries[i])) {
                user_chars[i] = input_char;
                break;
            } else {
                printf("Incorrect. Try again.\n");
            }
        }
    }
    user_chars[7] = '\0';
    getchar();

    printf("\nCombine characters into the keyword: ");
    char user_word[20];
    fgets(user_word, sizeof(user_word), stdin);
    user_word[strcspn(user_word, "\n")] = 0;

    if (isEasterEgg(user_word)) {
        printf("\n##Easter Egg Discovered!$$\n");
        printf("%s\n", arthur.message);
    } else {
        printf("Incorrect keyword. Returning to menu.\n");
    }
}

// === Main Menu ===

void mentoringMenu() {
    char input[20];
    while (1) {
        printf("\n--- Self-Management & Teamwork Menu ---\n");
        printf("A. Mentoring\n");
        printf("B. Trauma Management\n");
        printf("Q. Exit Program\n");
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0 || strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) break;
        else if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0) matchMentoring();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0) overcomeTrauma();
        else if (strcmp(input, "Arthur") == 0 || strcmp(input, "arthur") == 0) find_easter_egg();
        else printf("Invalid input.\n");
    }
}

// === Main Function ===

int main() {
    srand(time(NULL));
    mentoringMenu();
    return 0;
}