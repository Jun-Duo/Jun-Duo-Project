
#ifndef __reserve_H__
#define __reserve_H__

#include <stdbool.h>

#include "dateTime.h"
#include "field.h"

#define MAX_LEN_NAME 100
#define RESERVE_TIME_LIMIT 120

// Structure of a Reservation
typedef struct reserve {
    enum Field field;
    DateTime startTime;
    DateTime endTime;
    char name[MAX_LEN_NAME];
} Reserve;

// Declaration of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n);
void ReadReservation(Reserve *r);
void ListReservation(Reserve *r[], int count);
void UpdateReserve(Reserve *r[], int count);
void DeleteReserve(Reserve *r[], int count);
bool IsValidDateTime(Reserve *r[], int count, int idx);

// Definition of CRUD Functions for Reservation
void CreateReservation(Reserve *r[], int *count, int max_n) {
    // Check if out of range
    if (count >= max_n) {
        printf("�ִ� ���� ���� ���� �ʰ��߽��ϴ�.\n");
        return;
    }

    // Input Field for reserve
    
    printf("������ �ʵ带 �������ּ���.: ");

    // Input Reservation DateTime
    printf("������ ���۽ð��� �Է����ּ���(YYYYMMDD HH:MM): ");
    setDateTime(r[*count]->startTime);  // set start time
    int playTime;
    for (;;) {
        // Input playTime
        printf("�� �� ���� �����ðڽ��ϱ�?(�ִ� %d��): ", RESERVE_TIME_LIMIT);
        scanf("%d", &playTime);
        // Check if olayTime is more than time limit
        if (playTime > RESERVE_TIME_LIMIT) {
            printf("�ִ� ���� �ð�(%d��)�� �ʰ��߽��ϴ�.\n", RESERVE_TIME_LIMIT);
            continue;
        }
        // Calculate endTime
        r[*count]->endTime = CalculateDateTime(&r[*count]->startTime, playTime);
        // Check if is Valid
        if (IsValidDateTime(r, count, *count) == true) {
            break;
        } else {
            printf("���� ����ð��� ��Ĩ�ϴ�.\n");
            continue;
        }
    }
}

void ReadReservation(Reserve *r) {
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