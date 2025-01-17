#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 200

typedef struct {
    int id;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int age;
} Record;

void clearConsole() {

}

int loadRecords(const char* fileName, Record records[], int maxRecords) {

    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        printf("Nie udalo sie otworzyc pliku %s\n", fileName);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    fgets(buffer, MAX_LINE_LENGTH, fp);

    while (fgets(buffer, MAX_LINE_LENGTH, fp) && count < maxRecords) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        char* token = strtok(buffer, ",");
        if (!token) continue;
        records[count].id = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(records[count].firstName, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(records[count].lastName, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        if (!token) continue;
        records[count].age = atoi(token);

        count++;
    }

    fclose(fp);
    return count;
}

void listRecordsView(Record records[], int recordCount) {
    printf("\n -- LISTA REKORDOW --\n\n");

    for (int i = 0; i < recordCount; i++) {
        printf("ID: %d | %s %s\n",
               records[i].id,
               records[i].firstName,
               records[i].lastName);
    }

    int running = 1;

    while (running) {
        printf("\n1. Wroc do menu glownego\n");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                return;
            default:
                printf("Nieznana opcja. Sprobuj ponownie.\n");
                break;
        }
    }
}

int main(void) {
    const char* fileName = "dane.csv";
    const int MAX_RECORDS = 100;

    Record records[MAX_RECORDS];
    int recordCount = 0;

    recordCount = loadRecords(fileName, records, MAX_RECORDS);

    int running = 1;

    while (running) {
        clearConsole();

        printf("Wczytano %d rekordow z pliku %s\n\n", recordCount, fileName);

        printf("--- MENU ---\n\n");
        printf("1. Lista rekordow\n");
        printf("9. Wylacz program\n");
        printf("\nWybierz opcje:\n");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                clearConsole();
                listRecordsView(records, recordCount);
                break;
            case 9:
                running = 0;
                printf("Koniec programu.\n");
                break;
            default:
                printf("Nieznana opcja.\n");
        }
    }


    return 0;
}