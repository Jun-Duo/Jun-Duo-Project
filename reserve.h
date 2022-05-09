
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
        printf("�ִ� ���� ���� ���� �ʰ��߽��ϴ�.\n");
        return;
    }
    printf("������ ���۽ð��� �Է����ּ���(YYYYMMDD HH:MM): ");
    setDateTime(r[*count]->startTime); // set start time
    int playTime;
    printf("�� �� ���� �����ðڽ��ϱ�?: ");
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