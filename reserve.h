
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

// CRUD Functions for Reservation
void CreateReservation(Reserve *r) {
}

void ReadReservation(Reserve p) {
}

void ListReservation(Reserve *r[], int count) {
}

void UpdateReserve(Reserve *r[], int count) {
}

void DeleteReserve(Reserve *r[], int count) {
}

#endif