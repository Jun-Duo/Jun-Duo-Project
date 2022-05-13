#ifndef __manager_H__
#define __manager_H__

#include "reserve.h"

//Declare Functions
void SearchReservation(Reserve *r[], int count);
void SearchReservationName(Reserve *r[], int count);
void SearchReservationDate(Reserve *r[], int count);
void SearchReservationTime(Reserve *r[], int count);
void SearchReservationField(Reserve *r[], int count);
// Searching Data Functions

void SearchReservation(Reserve *r[], int count) { // 메인 검색
    int choice;
    printf("-------------");
    printf("\n검색할 항목을 고르시오.\n");
    printf("1. 예약자의 이름\n");
    printf("2. 예약 날짜\n");
    printf("3. 예약 시간\n");
    printf("4. 예약 장소\n");
    printf("==>");
    scanf("%d", &choice);
    while(1){
        if(choice == 1){
            SearchReservationName(r, count);
            break;
        }   
        
        else if(choice == 2){
            SearchReservationDate(r, count);//예약 날짜
            break;
        }

        else if(choice == 3){
            SearchReservationTime(r, count);//예약 시간
            break;
        }

        else if(choice == 4){
            SearchReservationField(r, count);//예약 장소
            break;
        }
        
        else printf("잘못 입력하였습니다. 다시 입력하시오.");
        }
}

void SearchReservationName(Reserve *r[], int count) { // 예약자 이름
    char search_name[30];
    int flag = 0;
    getchar();
    printf("찾을 예약자의 입력을 입력하시오. : ");
    fgets(search_name,30,stdin);
    search_name[strlen(search_name) - 1] = '\0';
    printf("\n번호  예약자명\t 예약필드\t 예약시간\n");
    for(int i=0; i<count; i++){
        if(strstr(r[i]->name,search_name)){//이름을 찾았다면
            printf(" %d%10s\t%10s\t (", i+1, r[i]->name, fieldName[r[i]->field]);
            PrintDateTime(&r[i]->startTime);
            printf(" ~ ");
            PrintDateTime(&r[i]->endTime);
            printf(")\n");
            flag++;
        }
    }
    if(flag == 0) printf("\t\t!!No search result!!\n");
}


void SearchReservationDate(Reserve *r[], int count) { // 예약 날짜
    char search_date[30];
    int flag = 0;
    getchar();
    printf("찾을 예약 날짜를 입력하시오. : ");
    fgets(search_date,30,stdin);
    search_date[strlen(search_date) - 1] = '\0';
    printf("\n번호  예약자명\t 예약필드\t 예약날짜\n");
    // for(int i=0; i<count; i++){
    //     if(strstr(r[i]->dt_year,search_date)){//이름을 찾았다면
    //         printf(" %d%10s\t%10s\t (", i+1, r[i]->name, fieldName[r[i]->field]);
    //         PrintDateTime(&r[i]->startTime);
    //         printf(")\n");
    //         flag++;
    //     }
    // }
    if(flag == 0) printf("\t\t!!No search result!!\n");
}

void SearchReservationTime(Reserve *r[], int count) { // 예약 시간
    char search_time[30];
    int flag = 0;
    getchar();
    printf("찾을 예약 시간을 입력하시오. : ");
    fgets(search_time,30,stdin);
    search_time[strlen(search_time) - 1] = '\0';
    printf("\n번호  예약자명\t 예약필드\t 예약시간\n");
    // for(int i=0; i<count; i++){
    //     if(strstr(r[i]->startTime,search_time)){//이름을 찾았다면
    //         printf(" %d%10s\t%10s\t (", i+1, r[i]->name, fieldName[r[i]->field]);
    //         PrintDateTime(&r[i]->startTime);
    //         printf(")\n");
    //         flag++;
    //     }
    // }
    // if(flag == 0) printf("\t\t!!No search result!!\n");
}


void SearchReservationField(Reserve *r[], int count) { // 예약 장소
    int flag = 0;
    int field_num;
    char search_name[30];
    printf("찾을 예약 장소를 입력하시오. : 1. 평봉필드, 2. 히딩크풋살장");
    scanf("%d", &field_num);
    // if(field_num == 1){
    //     strcpy(search_name, "PyeongBong_Field");
    // }
    // else if(field_num == 2){
    //     strcpy(search_name, "Hiddink_Futsal_Field");
    // }
    // printf("\n번호  예약자명\t 예약필드\t 예약시간\n");
    // for(int i=0; i<count; i++){
    //     if(strstr(r[i]->field, search_name)){//이름을 찾았다면
    //         printf(" %d%10s\t%10s\t (", i+1, r[i]->field, fieldName[r[i]->field]);
    //         PrintDateTime(&r[i]->startTime);
    //         printf(" ~ ");
    //         PrintDateTime(&r[i]->endTime);
    //         printf(")\n");
    //         flag++;
    //     }
    }
    if(flag == 0) printf("\t\t!!No search result!!\n");
}


// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count) { // 파일 입력
}

int SaveAsFile(char *filename, Reserve *r[], int count) { // 파일 출력
}

#endif