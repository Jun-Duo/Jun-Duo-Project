#ifndef __reserve_H__
#define __reserve_H__
#include "reserve.h"
#endif

// Searching Data Functions
void SearchReservation(Reserve *r[], int count); // 메인 검색
void SearchReservationName(Reserve *r[], int count); // 예약자 이름
void SearchReservationDate(Reserve *r[], int count); // 예약 날짜
void SearchReservationTime(Reserve *r[], int count); // 예약 시간
void SearchReservationField(Reserve *r[], int count); // 예약 장소

// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count); // 파일 입력
int SaveAsFile(char *filename, Reserve *r[], int count); // 파일 출력