#ifndef __manager_H__
#define __manager_H__

#include "reserve.h"

// Searching Data Functions
void SearchReservation(Reserve *r[], int count) { // 메인 검색
    printf("검색할 항목을 고르시오.\n");
    printf("1. 예약자의 이름\n");
    printf("2. 예약 날짜\n");
    printf("3. 예약 시간\n");
    printf("4. 예약 장소\n");

}

void SearchReservationName(Reserve *r[], int count) { // 예약자 이름
}

void SearchReservationDate(Reserve *r[], int count) { // 예약 날짜
}

void SearchReservationTime(Reserve *r[], int count) { // 예약 시간
}

void SearchReservationField(Reserve *r[], int count) { // 예약 장소
}


// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count) { // 파일 입력
}

int SaveAsFile(char *filename, Reserve *r[], int count) { // 파일 출력
}

#endif