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

int LoadFromFile(char *filename, Reserve *r[], int *count);
int SaveAsFile(char *filename, Reserve *r[], int count);

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
            SearchReservationDateTime(r, count); // 예약 날짜 및 시간
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
int LoadFromFile(char *filename, Reserve *r[], int *count) {  // 파일 입력
}

int SaveAsFile(char *filename, Reserve *r[], int count) {  // 파일 출력
}

#endif