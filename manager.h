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
void SearchReservation(Reserve *r[], int count) {  // 메인 검색
    int choice;
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
        case 1:
            SearchReservationName(r, count);  // 예약자명
            break;
        case 2:
            SearchReservationDateTime(r, count);  // 예약 날짜 및 시간
            break;
        case 3:
            SearchReservationDate(r, count);  //예약 날짜
            break;
        case 4:
            SearchReservationTime(r, count);  //예약 시간
            break;
        case 5:
            SearchReservationField(r, count);  //예약 장소
            break;
        default:
            printf("잘못된 입력!\n");
    }
}

void SearchReservationName(Reserve *r[], int count) {  // 예약자 이름
    char searchName[MAX_LEN_NAME];
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    printf("검색할 예약자명을 입력해주세요.: ");
    fgets(searchName, MAX_LEN_NAME, stdin);
    searchName[strlen(searchName) - 1] = '\0';

    for (int i = 0; i < count; i++) {
        if (strstr(r[i]->name, searchName)) {  // 이름을 찾았다면
            if (searchCount == 0)              // 첫 번째 검색 결과
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

void SearchReservationDateTime(Reserve *r[], int count) {  // 예약 날짜
    DateTime searchDateTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");
        SetDateTime(&searchDateTime);
        if (!IsValidDate(&searchDateTime) || !IsValidTime(&searchDateTime)) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDateTime, &r[i]->startTime) == 0) {
            if (CompareTime(&searchDateTime, &r[i]->startTime) != -1 && CompareTime(&searchDateTime, &r[i]->endTime) != 1) {  // 해당 시간 예약을 찾았다면
                if (searchCount == 0)                                                                                         // 첫 번째 검색 결과
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

void SearchReservationDate(Reserve *r[], int count) {  // 예약 날짜
    DateTime searchDate;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 날짜를 입력해주세요(YYYYMMDD): ");
        SetDate(&searchDate);
        if (!IsValidDate(&searchDate)) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareDate(&searchDate, &r[i]->startTime) == 0) {  // 해당 날짜 예약을 찾았다면
            if (searchCount == 0)                               // 첫 번째 검색 결과
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

void SearchReservationTime(Reserve *r[], int count) {  // 예약 시간
    DateTime searchTime;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        printf("검색할 예약 시간를 입력해주세요(HH:MM): ");
        SetTime(&searchTime);
        if (!IsValidTime(&searchTime)) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (CompareTime(&searchTime, &r[i]->startTime) != -1 && CompareTime(&searchTime, &r[i]->endTime) != 1) {  // 해당 시간이 포함된 예약을 찾았다면
            if (searchCount == 0)                                                                                 // 첫 번째 검색 결과
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

void SearchReservationField(Reserve *r[], int count) {  // 예약 장소
    enum Field searchField;
    int searchCount = 0;
    while (getchar() != '\n')
        ;
    for (;;) {
        PrintFieldList();
        printf("검색할 예약 장소를 선택해주세요.: ");
        scanf("%d", &searchField);
        if (searchField < 1 || searchField > NUM_FIELDS) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        if (searchField == r[i]->field) {  // 해당 장소 예약을 찾았다면
            if (searchCount == 0)          // 첫 번째 검색 결과
                printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
            printf("%4d ", i + 1);
            ReadReservation(r[i]);
            searchCount++;
        }
    }
    if (searchCount == 0)
        printf("검색 결과가 없습니다.\n");
}

// File I/O Functions
#define MAX_LEN_FILE_NAME 100
#define MAX_LEN_DATA_STRING 1000
void LoadFromFile(Reserve *r[], int *count, int max_n) {  // 파일 입력
    char inputFileName[MAX_LEN_FILE_NAME];
    FILE *input = NULL;

    // Check if out of range
    if (*count >= max_n) {
        printf("최대 예약 정보 수를 초과했습니다.\n");
        return;
    }

    while (getchar() != '\n')
        ;
    printf("불러 올 파일 이름을 입력해주세요.: ");
    fgets(inputFileName, MAX_LEN_FILE_NAME - 1, stdin);
    inputFileName[strlen(inputFileName) - 1] = '\0';

    input = fopen(inputFileName, "r");
    if (input == NULL) {
        printf("파일을 불러오는데 실패했습니다.\n");
        return;
    }

    int i = *count;
    char dataString[MAX_LEN_DATA_STRING];

    while (!feof(input)) {
        r[i]->isValid = false;

        fgets(dataString, MAX_LEN_DATA_STRING, input);

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
    printf("데이터 불러오기에 성공했습니다.\n");
}

void SaveAsFile(Reserve *r[], int count) {  // 파일 출력
}

#endif