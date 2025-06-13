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
    char project_name[100] = "K-POP Audition 2025"; // Example project name
    int total_judges = 5;
    int selected_members = 3;

    // Preloaded judge data
    strcpy(judges[0].name, "Youngsoo");
    strcpy(judges[0].gender, "Male");
    strcpy(judges[0].affiliation, "JYK Studio");
    strcpy(judges[0].title, "Producer");
    strcpy(judges[0].specialty, "Music");
    strcpy(judges[0].email, "youngsu@outlook.com");
    strcpy(judges[0].phone, "010-1234-5678");

    strcpy(judges[1].name, "Jiyoung");
    strcpy(judges[1].gender, "Female");
    strcpy(judges[1].affiliation, "DK Studio");
    strcpy(judges[1].title, "Director");
    strcpy(judges[1].specialty, "Dance");
    strcpy(judges[1].email, "jiyounghere@outlook.com");
    strcpy(judges[1].phone, "010-2345-6789");

    strcpy(judges[2].name, "Minjun");
    strcpy(judges[2].gender, "Male");
    strcpy(judges[2].affiliation, "JM Studio");
    strcpy(judges[2].title, "Director");
    strcpy(judges[2].specialty, "Vocal");
    strcpy(judges[2].email, "minjun@outlook.com");
    strcpy(judges[2].phone, "010-3456-7890");

    strcpy(judges[3].name, "Hyunwoo");
    strcpy(judges[3].gender, "Male");
    strcpy(judges[3].affiliation, "Starlight Entertainment");
    strcpy(judges[3].title, "Director");
    strcpy(judges[3].specialty, "Visual");
    strcpy(judges[3].email, "hyunwoo@outlook.com");
    strcpy(judges[3].phone, "010-4567-8901");

    strcpy(judges[4].name, "Jiyoung");
    strcpy(judges[4].gender, "Female");
    strcpy(judges[4].affiliation, "Association");
    strcpy(judges[4].title, "Critic");
    strcpy(judges[4].specialty, "Critic");
    strcpy(judges[4].email, "jiyoung@outlook.com");
    strcpy(judges[4].phone, "010-5678-9012");

    // Output
    printf("\n=======================\n");
    printf("  Judge Information\n");
    printf("=======================\n");
    printf("Project: %s\n", project_name);
    printf("Total Judges: %d, Selected Members: %d\n", total_judges, selected_members);
    printf("-----------------------\n");

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

    return 0;
}
