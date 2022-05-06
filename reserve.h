
#ifndef __dateTime_H__
#define __dateTime_H__
#include "dateTime.h"
#endif

#ifndef __field_H__
#define __field_H__
#include "field.h"
#endif

#define MAX_LEN_NAME 100

// Structure of a Reservation
typedef struct reserve {
    Field field;
    DateTime startTime;
    DateTime endTime;
    char name[MAX_LEN_NAME];
    int numOfMemebers;
} Reserve;

// CRUD Functions for Reservation
void CreateReservation(Reserve *r);
void ReadReservation(Reserve p);
void ListReservation(Reserve *r[], int count);
void UpdateReserve(Reserve *r[], int count);
void DeleteReserve(Reserve *r[], int count);