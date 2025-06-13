#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char gender[10];
    char affiliation[100];
    char title[100];
    char specialty[50];
    char email[100];
    char phone[20];
} Judge;

int main() {
    Judge judges[MAX];
    char project_name[100];
    int total_judges, selected_members;
    char view_option;

    // Project details
    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // clear newline from input buffer

    printf("========================================\n");
    printf("Starting to input information for %d judges\n", total_judges);
    printf("========================================\n");

    // Input judges
    for (int i = 0; i < total_judges; i++) {
        printf("\nJudge %d\n", i + 1);
        printf("Name: ");
        fgets(judges[i].name, sizeof(judges[i].name), stdin);
        judges[i].name[strcspn(judges[i].name, "\n")] = '\0';

        printf("Gender: ");
        fgets(judges[i].gender, sizeof(judges[i].gender), stdin);
        judges[i].gender[strcspn(judges[i].gender, "\n")] = '\0';

        printf("Affiliation: ");
        fgets(judges[i].affiliation, sizeof(judges[i].affiliation), stdin);
        judges[i].affiliation[strcspn(judges[i].affiliation, "\n")] = '\0';

        printf("Title: ");
        fgets(judges[i].title, sizeof(judges[i].title), stdin);
        judges[i].title[strcspn(judges[i].title, "\n")] = '\0';

        printf("Specialty: ");
        fgets(judges[i].specialty, sizeof(judges[i].specialty), stdin);
        judges[i].specialty[strcspn(judges[i].specialty, "\n")] = '\0';

        printf("Email: ");
        fgets(judges[i].email, sizeof(judges[i].email), stdin);
        judges[i].email[strcspn(judges[i].email, "\n")] = '\0';

        printf("Phone: ");
        fgets(judges[i].phone, sizeof(judges[i].phone), stdin);
        judges[i].phone[strcspn(judges[i].phone, "\n")] = '\0';
    }

    printf("\nDo you want to display the judges' information? (Y/N): ");
    scanf(" %c", &view_option);

    if (view_option == 'Y' || view_option == 'y') {
        printf("\n=======================\n");
        printf("  Judge Information\n");
        printf("=======================\n");
        for (int i = 0; i < total_judges; i++) {
            printf("[Judge %d]\n", i + 1);
            printf("Name       : %s\n", judges[i].name);
            printf("Gender     : %s\n", judges[i].gender);
            printf("Affiliation: %s\n", judges[i].affiliation);
            printf("Title      : %s\n", judges[i].title);
            printf("Specialty  : %s\n", judges[i].specialty);
            printf("Email      : %s\n", judges[i].email);
            printf("Phone      : %s\n", judges[i].phone);
            printf("-----------------------------\n");
        }
    } else {
        printf("Program terminated.\n");
    }

    return 0;
}