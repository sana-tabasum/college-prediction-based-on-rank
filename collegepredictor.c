#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512

struct College {
    char name[100];
    char branch[50];
    char category[10];
    int closingRank;
};

int main() {
    struct College colleges[1000];
    int count = 0;
    FILE *fp = fopen("cutoff.csv", "r");

    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, fp); // Skip header line

    while (fgets(line, MAX_LINE, fp)) {
        char *token = strtok(line, ",");
        if (!token) continue;
        strcpy(colleges[count].name, token);

        token = strtok(NULL, ",");
        strcpy(colleges[count].branch, token);

        token = strtok(NULL, ",");
        strcpy(colleges[count].category, token);

        token = strtok(NULL, ",");
        colleges[count].closingRank = atoi(token);

        count++;
    }

    fclose(fp);

    int userRank;
    char userCategory[10];
    printf("Enter your rank: ");
    scanf("%d", &userRank);
    printf("Enter your category (e.g., OC, BC, SC): ");
    scanf("%s", userCategory);

    printf("\nPredicted Colleges:\n");
    printf("------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(colleges[i].category, userCategory) == 0 &&
            userRank <= colleges[i].closingRank) {
            printf("%s - %s (Closing Rank: %d)\n",
                   colleges[i].name,
                   colleges[i].branch,
                   colleges[i].closingRank);
            found = 1;
        }
    }

    if (!found) {
        printf("No colleges found for your rank and category.\n");
    }

    return 0;
}
