
#ifndef __reserve_H__
#define __reserve_H__

#include <stdbool.h>

#include "dateTime.h"
#include "field.h"

#define MAX_LEN_NAME 100

// Structure of a Reservation
typedef struct reserve {
    enum Field field;
    DateTime startTime;
    DateTime endTime;
    char name[MAX_LEN_NAME];
} Reserve;

// Declaration of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n);
void ReadReservation(Reserve p);
void ListReservation(Reserve *r[], int count);
void UpdateReserve(Reserve *r[], int count);
void DeleteReserve(Reserve *r[], int count);
bool IsValidDateTime(Reserve *r[], int count, int idx);

// Definition of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n) {
    if (count >= max_n) {
        printf("최대 예약 정보 수를 초과했습니다.\n");
        return;
    }
    printf("예약할 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");
    setDateTime(r[*count]->startTime);  // set start time
    int playTime;
    for (;;) {
        printf("몇 분 동안 빌리시겠습니까?(최대 120분): ");
        scanf("%d", &playTime);
        if (playTime > 120) {
            printf("최대 예약 시간(120분)을 초과했습니다.\n");
        } else {
            break;
        }
    }
    r[*count]->endTime = CalculateDateTime(&r[*count]->startTime, playTime);
    int inValidDateTime = IsValidDateTime(r, count, *count);
}

void ReadReservation(Reserve p) {
}

void ListReservation(Reserve *r[], int count) {
}

void UpdateReserve(Reserve *r[], int count) {
}

void DeleteReserve(Reserve *r[], int count) {
}

bool IsValidDateTime(Reserve *r[], int count, int idx) {
    for (int i = 0; i < count; i++) {
        if (i == idx) continue;

        if (CompareDateTime(&r[i]->startTime, &r[idx]->endTime) == 1 || CompareDateTime(&r[i]->endTime, &r[idx]->startTime) == -1)
            continue;
        else
            return false;
    }
    return true;
}

#endif