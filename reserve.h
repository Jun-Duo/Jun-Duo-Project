
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
        printf("�ִ� ���� ���� ���� �ʰ��߽��ϴ�.\n");
        return;
    }

    // Input Reservator's Name
    while (getchar() != '\n')
        ;
    printf("������ ������ �Է����ּ���.: ");
    fgets(r[*count]->name, MAX_LEN_NAME, stdin);
    r[*count]->name[strlen(r[*count]->name) - 1] = '\0';

    // Input Field for reserve
    int _int_field;
    for (;;) {
        PrintFieldList();  // Print Field List
        printf("������ �ʵ带 �������ּ���.: ");
        scanf("%d", &_int_field);
        if (_int_field >= 1 && _int_field <= NUM_FIELDS) {
            r[*count]->field = _int_field - 1;
            break;
        } else {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        }
    }

    // Input Reservation DateTime
    for (;;) {
        printf("������ ���۽ð��� �Է����ּ���(YYYYMMDD HH:MM): ");
        SetDateTime(&r[*count]->startTime);  // set start time
        if (!IsValidDate(&r[*count]->startTime) || !IsValidTime(&r[*count]->startTime)) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        }
        int playTime;
        // Input playTime
        printf("�� �� ���� �����ðڽ��ϱ�?(�ִ� %d��): ", RESERVE_TIME_LIMIT);
        scanf("%d", &playTime);
        // Check if olayTime is more than time limit
        if (playTime > RESERVE_TIME_LIMIT) {
            printf("�ִ� ���� �ð�(%d��)�� �ʰ��߽��ϴ�.\n", RESERVE_TIME_LIMIT);
            continue;
        }
        // Calculate endTime
        CalculateDateTime(&r[*count]->endTime, &r[*count]->startTime, playTime);
        // Check if is Valid
        if (IsValidDateTimeToReserve(r, *count, *count) == true) {
            break;
        } else {
            printf("���� ����� ��Ĩ�ϴ�.\n");
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
    printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
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
    printf("������ ������ �������ּ���.: ");
    scanf("%d", &updateIdx);
    updateIdx--;

    if (updateIdx > count || updateIdx < 0) {
        printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n\n");
        return;
    }

    // Input Reservator's Name
    while (getchar() != '\n')
        ;
    printf("������ ������ ������ �Է����ּ���.: ");
    fgets(r[updateIdx]->name, MAX_LEN_NAME, stdin);
    r[updateIdx]->name[strlen(r[updateIdx]->name) - 1] = '\0';

    // Input Field for reserve
    int _int_field;
    for (;;) {
        PrintFieldList();  // Print Field List
        printf("���� ������ �ʵ带 �������ּ���.: ");
        scanf("%d", &_int_field);
        if (_int_field >= 1 && _int_field <= NUM_FIELDS) {
            r[updateIdx]->field = _int_field - 1;
            break;
        } else {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        }
    }

    // Input Reservation DateTime
    for (;;) {
        printf("���� ������ ���۽ð��� �Է����ּ���(YYYYMMDD HH:MM): ");
        SetDateTime(&r[updateIdx]->startTime);  // set start time
        if (!IsValidDate(&r[updateIdx]->startTime) || !IsValidTime(&r[updateIdx]->startTime)) {
            printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n");
            continue;
        }
        int playTime;
        // Input playTime
        printf("�� �� ���� �����ðڽ��ϱ�?(�ִ� %d��): ", RESERVE_TIME_LIMIT);
        scanf("%d", &playTime);
        // Check if olayTime is more than time limit
        if (playTime > RESERVE_TIME_LIMIT) {
            printf("�ִ� ���� �ð�(%d��)�� �ʰ��߽��ϴ�.\n", RESERVE_TIME_LIMIT);
            continue;
        }
        // Calculate endTime
        CalculateDateTime(&r[updateIdx]->endTime, &r[updateIdx]->startTime, playTime);
        // Check if is Valid
        if (IsValidDateTimeToReserve(r, count, updateIdx) == true) {
            break;
        } else {
            printf("���� ����� ��Ĩ�ϴ�.\n");
            continue;
        }
    }
}

void DeleteReservation(Reserve *r[], int *count) {
    // Print the list of reservation
    ListReservation(r, *count);

    // Input which reservation to update
    int deleteIdx = -1;
    printf("������ ������ �������ּ���.: ");
    scanf("%d", &deleteIdx);
    deleteIdx--;

    if (deleteIdx > *count || deleteIdx < 0) {
        printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n\n");
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