
#ifndef __reserve_H__
#define __reserve_H__

#include "dateTime.h"
#include "field.h"

#define MAX_LEN_NAME 100

// Structure of a Reservation
typedef struct reserve {
    enum Field field;
    DateTime startTime;
    DateTime endTime;
    char name[MAX_LEN_NAME];
    int numOfMemebers;
} Reserve;

// Declaration of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n);
void ReadReservation(Reserve p);
void ListReservation(Reserve *r[], int count);
void UpdateReserve(Reserve *r[], int count);
void DeleteReserve(Reserve *r[], int count);
int IsValidDateTime(Reserve *r[], int count);

// Definition of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n) {
    if (count >= max_n) {
        printf("최대 예약 정보 수를 초과했습니다.\n");
        return;
    }
    printf("예약할 시작시간을 입력해주세요(YYYYMMDD HH:MM): ");
    setDateTime(r[*count]->startTime); // set start time
    int playTime;
    printf("몇 분 동안 빌리시겠습니까?: ");
    scanf("%d", &playTime);
    
}

void ReadReservation(Reserve p) {
}

void ListReservation(Reserve *r[], int count) {
}

void UpdateReserve(Reserve *r[], int count) {
}

void DeleteReserve(Reserve *r[], int count) {
}

int IsValidDateTime(Reserve *r[], int count) {
}

#endif