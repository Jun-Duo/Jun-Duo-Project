#ifndef __manager_H__
#define __manager_H__

#include "reserve.h"

// Declare Functions
void SearchReservation(Reserve *r[], int count);
void SearchReservationName(Reserve *r[], int count);
void SearchReservationDateTime(Reserve *r[], int count);
void SearchReservationDate(Reserve *r[], int count);
void SearchReservationTime(Reserve *r[], int count);
void SearchReservationField(Reserve *r[], int count);

void LoadFromFile(Reserve *r[], int *count, int max_n);
void SaveAsFile(Reserve *r[], int count);

// Searching Data Functions
void SearchReservation(Reserve *r[], int count) {  // ���� �˻�
    int choice;
    printf("\n");
    printf("1. �����ڸ�\n");
    printf("2. ���� ��¥ �� �ð�\n");
    printf("3. ���� ��¥\n");
    printf("4. ���� �ð�\n");
    printf("5. ���� ���\n");
    printf("-----------------\n");
    printf("�˻��� �׸��� �������ּ���.: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            SearchReservationName(r, count);  // �����ڸ�
            break;
        case 2:
            SearchReservationDateTime(r, count); // ���� ��¥ �� �ð�
            break;
        case 3:
            SearchReservationDate(r, count);  //���� ��¥
            break;
        case 4:
            SearchReservationTime(r, count);  //���� �ð�
            break;
        case 5:
            SearchReservationField(r, count);  //���� ���
            break;
        default:
            printf("�߸��� �Է�!\n");
    }
}

void SearchReservationName(Reserve *r[], int count) {  // ������ �̸�
    char searchName[MAX_LEN_NAME];
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    printf("�˻��� �����ڸ��� �Է����ּ���.: ");
    fgets(searchName, MAX_LEN_NAME, stdin);
    searchName[strlen(searchName) - 1] = '\0';

    for (int i = 0; i < count; i++) {
        if (strstr(r[i]->name, searchName)) {  // �̸��� ã�Ҵٸ�
            if (searchCount == 0)              // ù ��° �˻� ���
                printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("�˻� ����� �����ϴ�.\n");
}

void SearchReservationDateTime(Reserve *r[], int count) {  // ���� ��¥
    DateTime searchDateTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("�˻��� ���� ���۽ð��� �Է����ּ���(YYYYMMDD HH:MM): ");
        SetDateTime(&searchDateTime);
        if (!IsValidDate(&searchDateTime) || !IsValidTime(&searchDateTime)) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDateTime, &r[i]->startTime) == 0) {
            if (CompareTime(&searchDateTime, &r[i]->startTime) != -1 && CompareTime(&searchDateTime, &r[i]->endTime) != 1) {  // �ش� �ð� ������ ã�Ҵٸ�
                if (searchCount == 0)                                                                                         // ù ��° �˻� ���
                    printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
                printf("%4d ", i + 1);
                ReadReservation(r[i]);
                searchCount++;
            }
        }
    }
    if (searchCount == 0)
        printf("�˻� ����� �����ϴ�.\n");
}

void SearchReservationDate(Reserve *r[], int count) {  // ���� ��¥
    DateTime searchDate;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("�˻��� ���� ��¥�� �Է����ּ���(YYYYMMDD): ");
        SetDate(&searchDate);
        if (!IsValidDate(&searchDate)) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDate, &r[i]->startTime) == 0) {  // �ش� ��¥ ������ ã�Ҵٸ�
            if (searchCount == 0)                               // ù ��° �˻� ���
                printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("�˻� ����� �����ϴ�.\n");
}

void SearchReservationTime(Reserve *r[], int count) {  // ���� �ð�
    DateTime searchTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("�˻��� ���� �ð��� �Է����ּ���(HH:MM): ");
        SetTime(&searchTime);
        if (!IsValidTime(&searchTime)) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareTime(&searchTime, &r[i]->startTime) != -1 && CompareTime(&searchTime, &r[i]->endTime) != 1) {  // �ش� �ð��� ���Ե� ������ ã�Ҵٸ�
            if (searchCount == 0)                                                                                 // ù ��° �˻� ���
                printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("�˻� ����� �����ϴ�.\n");
}

void SearchReservationField(Reserve *r[], int count) {  // ���� ���
    enum Field searchField;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        PrintFieldList();
        printf("�˻��� ���� ��Ҹ� �������ּ���.: ");
        scanf("%d", &searchField);
        if (searchField < 1 || searchField > NUM_FIELDS) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (searchField == r[i]->field) {  // �ش� ��� ������ ã�Ҵٸ�
            if (searchCount == 0)          // ù ��° �˻� ���
                printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("�˻� ����� �����ϴ�.\n");
}

// File I/O Functions
#define MAX_LEN_FILE_NAME 100
#define MAX_LEN_DATA_STRING 1000
void LoadFromFile(Reserve *r[], int *count, int max_n) {  // ���� �Է�
    char inputFileName[MAX_LEN_FILE_NAME];
    FILE *input = NULL;

    // Check if out of range
    if (*count >= max_n) {
        printf("�ִ� ���� ���� ���� �ʰ��߽��ϴ�.\n");
        return;
    }

    printf("�ҷ� �� ���� �̸��� �Է����ּ���.: ");
    fgets(inputFileName, MAX_LEN_FILE_NAME - 1, stdin);
    inputFileName[strlen(inputFileName) - 1] = '\0';
    
    FILE *input = fopen(inputFileName, "r");
    if (input == NULL) {
        printf("������ �ҷ����µ� �����߽��ϴ�.\n");
        return;
    }

    int i = *count;
    char dataString[MAX_LEN_DATA_STRING];

    while (!feof(input)) {
        fgets(dataString, MAX_LEN_DATA_STRING, input);

        if (feof(input)) // if End of File
            break;
        
        // Tokenize dataString
        char dataName[MAX_LEN_NAME] = strtok(dataString, ",");
        char dataField[MAX_LEN_FIELD_NAME] = strtok(NULL, ",");
        char dataStartTime[TIME_STR_LEN] = strtok(NULL, ",");
        char dataEndTime[TIME_STR_LEN] = strtok(NULL, ",");

        // name
        strcpy(r[i]->name, dataName);
        // field
        r[i]->field = 0;
        for (int i = 1; i <= NUM_FIELDS; i++) { // find field name
            if (!strcmp(dataField, fieldName[i])) { // if found field name
                r[i]->field = i;
                break;
            }
        }
        // startTime
        char startYYYYMMDD[8] = strtok(dataStartTime, " ");
        char startHH[2] = strtok(NULL, ":");
        char startMM[2] = strtok(NULL, "\n");
        r[i]->startTime->dt_year = atoi(startYYYYMMDD) / 10000;
        r[i]->startTime->dt_mon = atoi(startYYYYMMDD) / 100 % 100;
        r[i]->startTime->dt_day = atoi(startYYYYMMDD) % 100;
        r[i]->startTime->dt_hour = atoi(startHH);
        r[i]->startTime->dt_min = atoi(startMM);

        // endTime
        char endYYYYMMDD[8] = strtok(dataEndTime, " ");
        char endHH[2] = strtok(NULL, ":");
        char endMM[2] = strtok(NULL, "\n");
        r[i]->startTime->dt_year = atoi(endYYYYMMDD) / 10000;
        r[i]->startTime->dt_mon = atoi(endYYYYMMDD) / 100 % 100;
        r[i]->startTime->dt_day = atoi(endYYYYMMDD) % 100;
        r[i]->startTime->dt_hour = atoi(endHH);
        r[i]->startTime->dt_min = atoi(endMM);

        i++;
        (*count)++;
    }
}

void SaveAsFile(Reserve *r[], int count) {  // ���� ���
}

#endif