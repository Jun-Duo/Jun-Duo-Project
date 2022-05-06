#ifndef __reserve_H__
#define __reserve_H__
#include "reserve.h"
#endif

// Searching Data Functions
void SearchReservation(Reserve *r[], int count); // ���� �˻�
void SearchReservationName(Reserve *r[], int count); // ������ �̸�
void SearchReservationDate(Reserve *r[], int count); // ���� ��¥
void SearchReservationTime(Reserve *r[], int count); // ���� �ð�
void SearchReservationField(Reserve *r[], int count); // ���� ���

// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count); // ���� �Է�
int SaveAsFile(char *filename, Reserve *r[], int count); // ���� ���