// candidates.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_FIELDS 11
#define MAX_STR 200

char candidate01[NUM_FIELDS][MAX_STR] = {
    "Jiyeon Park", "2006/04/15", "F", "jiyeon@outlook.com", "South Korea",
    "18.5", "Dance", "Composition", "0", "ENFJ",
    "A passionate and creative dancer and composer ready to pursue dreams together."
};
char candidate02[NUM_FIELDS][MAX_STR] = {
    "Ethan Smith", "2005/08/22", "M", "ethan@outlook.com", "USA",
    "21.2", "Vocal", "Lyric Writing", "2", "ISTP",
    "A vocalist with a rich voice and songwriting skills, eager to share K-POP’s charm worldwide."
};
char candidate03[NUM_FIELDS][MAX_STR] = {
    "Suphanan Wong", "2004/01/05", "F", "suphanan@outlook.com", "Thailand",
    "19.0", "Dance", "Lyric Writing", "4", "INFJ",
    "Aspiring to move hearts with dynamic dance and emotional lyrics, becoming part of the Hallyu wave from Thailand."
};
char candidate04[NUM_FIELDS][MAX_STR] = {
    "Helena Silva", "2007/03/10", "F", "helena@outlook.com", "Brazil",
    "20.8", "Vocal", "Composition & Lyric Writing", "1", "ENFP",
    "A versatile singer from Brazil who wants to inspire through both music and lyrics."
};
char candidate05[NUM_FIELDS][MAX_STR] = {
    "Karolina Nowak", "2006/09/18", "F", "karolina@outlook.com", "Poland",
    "17.9", "Dance", "Composition", "2", "ISFP",
    "A composer and dancer from Poland, eager to convey emotions through music."
};
char candidate06[NUM_FIELDS][MAX_STR] = {
    "Liam Wilson", "2006/11/08", "M", "liam@outlook.com", "Australia",
    "20.1", "Dance", "Composition & Lyric Writing", "3", "ENTJ",
    "A passionate dancer and composer from Australia, determined to share his unique music through K-POP."
};

char (*candidates[NUM_CANDIDATES])[NUM_FIELDS][MAX_STR] = {
    &candidate01, &candidate02, &candidate03,
    &candidate04, &candidate05, &candidate06
};

const char* getTopikDisplay(const char* score) {
    if (strcmp(score, "0") == 0) return "Native";
    return score;
}

int main() {
    printf("\n####################################\n");
    printf("     Audition Candidate Data Review\n");
    printf("####################################\n");

    printf("===============================================================================================================\n");
    printf("Name            | DOB       | Gender | Email                 | Nationality  | BMI  | Primary  | Secondary  | TOPIK  | MBTI  |\n");
    printf("===============================================================================================================\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%-15s | %-8s | %-6s | %-21s | %-12s | %-4s | %-8s | %-10s | %-6s | %-5s |\n",
            (*candidates[i])[0],  // Name
            (*candidates[i])[1],  // DOB
            (*candidates[i])[2],  // Gender
            (*candidates[i])[3],  // Email
            (*candidates[i])[4],  // Nationality
            (*candidates[i])[5],  // BMI
            (*candidates[i])[6],  // Primary Skill
            (*candidates[i])[7],  // Secondary Skill
            getTopikDisplay((*candidates[i])[8]),  // TOPIK
            (*candidates[i])[9]   // MBTI
        );
        printf("---------------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", (*candidates[i])[10]);  // Introduction
        printf("---------------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}