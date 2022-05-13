#ifndef __manager_H__
#define __manager_H__

#include "reserve.h"

// enum of search menu
enum SearchMenu {
    NAME = 1,
    DATE_TIME,
    DATE,
    TIME,
    FIELD
};

/*
    Function Declarations
*/
void SearchReservation(Reserve *r[], int count);
void SearchReservationName(Reserve *r[], int count);
void SearchReservationDateTime(Reserve *r[], int count);
void SearchReservationDate(Reserve *r[], int count);
void SearchReservationTime(Reserve *r[], int count);
void SearchReservationField(Reserve *r[], int count);

void LoadFromFile(Reserve *r[], int *count, int max_n);
void SaveAsFile(Reserve *r[], int count);

/*
    Function Definitions
*/
// Main Search Function
void SearchReservation(Reserve *r[], int count) {
    enum SearchMenu choice;
    printf("\n");
    printf("1. 예약자명\n");
    printf("2. 예약 날짜 및 시간\n");
    printf("3. 예약 날짜\n");
    printf("4. 예약 시간\n");
    printf("5. 예약 장소\n");
    printf("-----------------\n");
    printf("검색할 항목을 선택해주세요.: ");
    scanf("%d", &choice);

    switch (choice) {
        case NAME:
            SearchReservationName(r, count);  // search by reservator's name
            break;
        case DATE_TIME:
            SearchReservationDateTime(r, count);  // search by reservation date and time
            break;
        case DATE:
            SearchReservationDate(r, count);  // search by reservation date
            break;
        case TIME:
            SearchReservationTime(r, count);  // search by reservation time
            break;
        case FIELD:
            SearchReservationField(r, count);  // search by reservation field
            break;
        default:
            printf("잘못된 입력!\n");
    }
}

// search by reservator's name
void SearchReservationName(Reserve *r[], int count) {
    char searchName[MAX_LEN_NAME];
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    printf("검색할 예약자명을 입력해주세요.: ");  // input name to search
    fgets(searchName, MAX_LEN_NAME, stdin);
    searchName[strlen(searchName) - 1] = '\0';

    for (int i = 0; i < count; i++) {
        if (strstr(r[i]->name, searchName)) {  // if found name
            if (searchCount == 0)              // if first result
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

// search by reservation date and time
void SearchReservationDateTime(Reserve *r[], int count) {
    DateTime searchDateTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");  // input dateTime to search
        SetDateTime(&searchDateTime);
        if (!IsValidDate(&searchDateTime) || !IsValidTime(&searchDateTime)) {  // check dateTime is valid
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDateTime, &r[i]->startTime) == 0) {
            if (CompareTime(&searchDateTime, &r[i]->startTime) != -1 && CompareTime(&searchDateTime, &r[i]->endTime) != 1) {  // if found reservation with searchDateTime
                if (searchCount == 0)                                                                                         // if first result
                    printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
                printf("%4d ", i + 1);
                ReadReservation(r[i]);
                searchCount++;
            }
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

// search by reservation date
void SearchReservationDate(Reserve *r[], int count) {
    DateTime searchDate;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 날짜를 입력해주세요(YYYYMMDD): ");  // input date to search
        SetDate(&searchDate);
        if (!IsValidDate(&searchDate)) {  // check date is valid
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDate, &r[i]->startTime) == 0) {  // if found reservation in searchDate
            if (searchCount == 0)                               // if first result
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

// search by reservation time
void SearchReservationTime(Reserve *r[], int count) {
    DateTime searchTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 시간를 입력해주세요(HH:MM): ");  // input time to search
        SetTime(&searchTime);
        if (!IsValidTime(&searchTime)) {  // check time is valid
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareTime(&searchTime, &r[i]->startTime) != -1 && CompareTime(&searchTime, &r[i]->endTime) != 1) {  // if found reservation include searchTime
            if (searchCount == 0)                                                                                 // if first result
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

// search by reservation field
void SearchReservationField(Reserve *r[], int count) {
    enum Field searchField;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        PrintFieldList();
        printf("검색할 예약 장소를 선택해주세요.: ");  // input field to search
        scanf("%d", &searchField);
        if (searchField < 1 || searchField > NUM_FIELDS) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (searchField == r[i]->field) {  // if found reservation on searchField
            if (searchCount == 0)          // if first result
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

#define MAX_LEN_FILE_NAME 100
#define MAX_LEN_DATA_STRING 1000

// File Input
void LoadFromFile(Reserve *r[], int *count, int max_n) {
    char inputFileName[MAX_LEN_FILE_NAME];
    FILE *input = NULL;

    // Check if out of range
    if (*count >= max_n) {
        printf("최대 예약 정보 수를 초과했습니다.\n");
        return;
    }

    while (getchar() != '\n')
        ;
    printf("불러 올 파일 이름을 입력해주세요.: "); // input filename to load
    fgets(inputFileName, MAX_LEN_FILE_NAME - 1, stdin);
    inputFileName[strlen(inputFileName) - 1] = '\0';

    input = fopen(inputFileName, "r");
    if (input == NULL) { // fail to load input file
        printf("파일을 불러오는데 실패했습니다.\n");
        return;
    }

    int i = *count;
    char dataString[MAX_LEN_DATA_STRING];

    while (!feof(input)) {
        r[i]->isValid = false;

        fgets(dataString, MAX_LEN_DATA_STRING, input); // read one line

        if (feof(input))  // if End of File
            break;

        // Tokenize dataString
        char *dataName = strtok(dataString, ",");
        char *dataField = strtok(NULL, ",");
        char *dataStartTime = strtok(NULL, ",");
        char *dataEndTime = strtok(NULL, ",");

        // name
        strcpy(r[i]->name, dataName);
        // field
        r[i]->field = 0;
        for (int j = 1; j <= NUM_FIELDS; j++) {      // find field name
            if (!strcmp(dataField, fieldName[j])) {  // if found field name
                r[i]->field = j;
                break;
            }
        }
        // startTime
        char *startYYYYMMDD = strtok(dataStartTime, " ");
        char *startHH = strtok(NULL, ":");
        char *startMM = strtok(NULL, ",");
        r[i]->startTime.dt_year = atoi(startYYYYMMDD) / 10000;
        r[i]->startTime.dt_mon = atoi(startYYYYMMDD) / 100 % 100;
        r[i]->startTime.dt_day = atoi(startYYYYMMDD) % 100;
        r[i]->startTime.dt_hour = atoi(startHH);
        r[i]->startTime.dt_min = atoi(startMM);

        // endTime
        char *endYYYYMMDD = strtok(dataEndTime, " ");
        char *endHH = strtok(NULL, ":");
        char *endMM = strtok(NULL, "\n");
        r[i]->endTime.dt_year = atoi(endYYYYMMDD) / 10000;
        r[i]->endTime.dt_mon = atoi(endYYYYMMDD) / 100 % 100;
        r[i]->endTime.dt_day = atoi(endYYYYMMDD) % 100;
        r[i]->endTime.dt_hour = atoi(endHH);
        r[i]->endTime.dt_min = atoi(endMM);

        r[i]->isValid = true;
        i++;
        (*count)++;
    }

    fclose(input);

    printf("데이터 불러오기에 성공했습니다.\n");
}

// File Output
void SaveAsFile(Reserve *r[], int count) {
    char outputFileName[MAX_LEN_FILE_NAME];
    FILE *output = NULL;

    while (getchar() != '\n')
        ;
    printf("내보낼 파일 이름을 입력해주세요.: "); // input filename to save
    fgets(outputFileName, MAX_LEN_FILE_NAME - 1, stdin);
    outputFileName[strlen(outputFileName) - 1] = '\0';

    output = fopen(outputFileName, "w");
    if (output == NULL) { // fail to save file
        printf("파일을 내보내는데 실패했습니다.\n");
        return;
    }

    // print to file
    for (int i = 0; i < count; i++) {
        if (r[i]->isValid == false) continue;
        fprintf(output, "%s,", r[i]->name);
        fprintf(output, "%s,", fieldName[r[i]->field]);
        fprintf(output, "%04d%02d%02d %02d:%02d,", r[i]->startTime.dt_year, r[i]->startTime.dt_mon, r[i]->startTime.dt_day, r[i]->startTime.dt_hour, r[i]->startTime.dt_min);
        fprintf(output, "%04d%02d%02d %02d:%02d,", r[i]->endTime.dt_year, r[i]->endTime.dt_mon, r[i]->endTime.dt_day, r[i]->endTime.dt_hour, r[i]->endTime.dt_min);
        fprintf(output, "\n");
    }

    fclose(output);

    printf("데이터 내보내기에 성공했습니다.\n");
}

#endif