
#ifndef __reserve_H__
#define __reserve_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dateTime.h"
#include "field.h"

#define MAX_LEN_NAME 100
#define RESERVE_TIME_LIMIT 120

// Structure of a Reservation
typedef struct reserve {
    bool isValid;
    enum Field field;
    DateTime startTime;
    DateTime endTime;
    char name[MAX_LEN_NAME];
} Reserve;

// Declaration of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n);
void ReadReservation(Reserve *r);
void ListReservation(Reserve *r[], int count);
void UpdateReservation(Reserve *r[], int count);
void DeleteReservation(Reserve *r[], int *count);
bool IsValidDateTimeToReserve(Reserve *r[], int count, int idx);

// Definition of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n) {
    r[*count]->isValid = false;

    // Check if out of range
    if (*count >= max_n) {
        printf("최대 예약 정보 수를 초과했습니다.\n");
        return;
    }

    // Input Reservator's Name
    while (getchar() != '\n')
        ;
    printf("예약자 성명을 입력해주세요.: ");
    fgets(r[*count]->name, MAX_LEN_NAME, stdin);
    r[*count]->name[strlen(r[*count]->name) - 1] = '\0';

    // Input Field for reserve
    int _int_field;
    for (;;) {
        PrintFieldList();  // Print Field List
        printf("예약할 필드를 선택해주세요.: ");
        scanf("%d", &_int_field);
        if (_int_field >= 1 && _int_field <= NUM_FIELDS) {
            r[*count]->field = _int_field - 1;
            break;
        } else {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        }
    }

    // Input Reservation DateTime
    for (;;) {
        printf("예약할 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");
        SetDateTime(&r[*count]->startTime);  // set start time
        if (!IsValidDate(&r[*count]->startTime) || !IsValidTime(&r[*count]->startTime)) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        }
        int playTime;
        // Input playTime
        printf("몇 분 동안 빌리시겠습니까?(최대 %d분): ", RESERVE_TIME_LIMIT);
        scanf("%d", &playTime);
        // Check if olayTime is more than time limit
        if (playTime > RESERVE_TIME_LIMIT) {
            printf("최대 예약 시간(%d분)을 초과했습니다.\n", RESERVE_TIME_LIMIT);
            continue;
        }
        // Calculate endTime
        CalculateDateTime(&r[*count]->endTime, &r[*count]->startTime, playTime);
        // Check if is Valid
        if (IsValidDateTimeToReserve(r, *count, *count) == true) {
            break;
        } else {
            printf("기존 예약과 겹칩니다.\n");
            continue;
        }
    }

    printf("\n");
    r[*count]->isValid = true;
    (*count)++;
}

void ReadReservation(Reserve *r) {
    printf("%10s\t\t%10s\t (", r->name, fieldName[r->field]);
    PrintDateTime(&r->startTime);
    printf(" ~ ");
    PrintDateTime(&r->endTime);
    printf(")\n");
}

void ListReservation(Reserve *r[], int count) {
    printf("일련번호  예약자명\t 예약필드\t 예약시간\n");
    for (int i = 0; i < count; i++) {
        if (r[i]->isValid == false) continue;
        printf("%4d ", i + 1);
        ReadReservation(r[i]);
    }
    printf("\n");
}

void UpdateReservation(Reserve *r[], int count) {
    // Print the list of reservation
    ListReservation(r, count);

    // Input which reservation to update
    int updateIdx = -1;
    printf("수정할 예약을 선택해주세요.: ");
    scanf("%d", &updateIdx);
    updateIdx--;

    if (updateIdx > count || updateIdx < 0) {
        printf("입력값이 유효하지 않습니다.\n\n");
        return;
    }

    // Input Reservator's Name
    while (getchar() != '\n')
        ;
    printf("수정할 예약자 성명을 입력해주세요.: ");
    fgets(r[updateIdx]->name, MAX_LEN_NAME, stdin);
    r[updateIdx]->name[strlen(r[updateIdx]->name) - 1] = '\0';

    // Input Field for reserve
    int _int_field;
    for (;;) {
        PrintFieldList();  // Print Field List
        printf("수정 예약할 필드를 선택해주세요.: ");
        scanf("%d", &_int_field);
        if (_int_field >= 1 && _int_field <= NUM_FIELDS) {
            r[updateIdx]->field = _int_field - 1;
            break;
        } else {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        }
    }

    // Input Reservation DateTime
    for (;;) {
        printf("수정 예약할 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");
        SetDateTime(&r[updateIdx]->startTime);  // set start time
        if (!IsValidDate(&r[updateIdx]->startTime) || !IsValidTime(&r[updateIdx]->startTime)) {
            printf("입력값이 유효하지 않습니다.\n");
            continue;
        }
        int playTime;
        // Input playTime
        printf("몇 분 동안 빌리시겠습니까?(최대 %d분): ", RESERVE_TIME_LIMIT);
        scanf("%d", &playTime);
        // Check if olayTime is more than time limit
        if (playTime > RESERVE_TIME_LIMIT) {
            printf("최대 예약 시간(%d분)을 초과했습니다.\n", RESERVE_TIME_LIMIT);
            continue;
        }
        // Calculate endTime
        CalculateDateTime(&r[updateIdx]->endTime, &r[updateIdx]->startTime, playTime);
        // Check if is Valid
        if (IsValidDateTimeToReserve(r, count, updateIdx) == true) {
            break;
        } else {
            printf("기존 예약과 겹칩니다.\n");
            continue;
        }
    }
}

void DeleteReservation(Reserve *r[], int *count) {
    // Print the list of reservation
    ListReservation(r, *count);

    // Input which reservation to update
    int deleteIdx = -1;
    printf("삭제할 예약을 선택해주세요.: ");
    scanf("%d", &deleteIdx);
    deleteIdx--;

    if (deleteIdx > *count || deleteIdx < 0) {
        printf("입력값이 유효하지 않습니다.\n\n");
        return;
    }

    r[deleteIdx]->isValid = false;
}

bool IsValidDateTimeToReserve(Reserve *r[], int count, int idx) {
    for (int i = 0; i < count; i++) {
        if (i == idx) continue;
        if (r[i]->isValid == false) continue;
        if (r[i]->field != r[i]->field) continue;

        if (CompareDateTime(&r[i]->startTime, &r[idx]->endTime) == 1 || CompareDateTime(&r[i]->endTime, &r[idx]->startTime) == -1)
            continue;
        else
            return false;
    }
    return true;
}

#endif