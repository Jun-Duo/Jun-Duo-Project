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

void SearchReservation(Reserve *r[], int count) { // ���� �˻�
    int choice;
    printf("-------------");
    printf("\n�˻��� �׸��� ���ÿ�.\n");
    printf("1. �������� �̸�\n");
    printf("2. ���� ��¥\n");
    printf("3. ���� �ð�\n");
    printf("4. ���� ���\n");
    printf("==>");
    scanf("%d", &choice);
    while(1){
        if(choice == 1){
            SearchReservationName(r, count);
            break;
        }   
        
        else if(choice == 2){
            SearchReservationDate(r, count);//���� ��¥
            break;
        }

        else if(choice == 3){
            SearchReservationTime(r, count);//���� �ð�
            break;
        }

        else if(choice == 4){
            SearchReservationField(r, count);//���� ���
            break;
        }
        
        else printf("�߸� �Է��Ͽ����ϴ�. �ٽ� �Է��Ͻÿ�.");
        }
}

void SearchReservationName(Reserve *r[], int count) { // ������ �̸�
    char search_name[30];
    int flag = 0;
    getchar();
    printf("ã�� �������� �Է��� �Է��Ͻÿ�. : ");
    fgets(search_name,30,stdin);
    search_name[strlen(search_name) - 1] = '\0';
    printf("\n��ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
    for(int i=0; i<count; i++){
        if(strstr(r[i]->name,search_name)){//�̸��� ã�Ҵٸ�
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


void SearchReservationDate(Reserve *r[], int count) { // ���� ��¥
    char search_date[30];
    int flag = 0;
    getchar();
    printf("ã�� ���� ��¥�� �Է��Ͻÿ�. : ");
    fgets(search_date,30,stdin);
    search_date[strlen(search_date) - 1] = '\0';
    printf("\n��ȣ  �����ڸ�\t �����ʵ�\t ���೯¥\n");
    // for(int i=0; i<count; i++){
    //     if(strstr(r[i]->dt_year,search_date)){//�̸��� ã�Ҵٸ�
    //         printf(" %d%10s\t%10s\t (", i+1, r[i]->name, fieldName[r[i]->field]);
    //         PrintDateTime(&r[i]->startTime);
    //         printf(")\n");
    //         flag++;
    //     }
    // }
    if(flag == 0) printf("\t\t!!No search result!!\n");
}

void SearchReservationTime(Reserve *r[], int count) { // ���� �ð�
    char search_time[30];
    int flag = 0;
    getchar();
    printf("ã�� ���� �ð��� �Է��Ͻÿ�. : ");
    fgets(search_time,30,stdin);
    search_time[strlen(search_time) - 1] = '\0';
    printf("\n��ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
    // for(int i=0; i<count; i++){
    //     if(strstr(r[i]->startTime,search_time)){//�̸��� ã�Ҵٸ�
    //         printf(" %d%10s\t%10s\t (", i+1, r[i]->name, fieldName[r[i]->field]);
    //         PrintDateTime(&r[i]->startTime);
    //         printf(")\n");
    //         flag++;
    //     }
    // }
    // if(flag == 0) printf("\t\t!!No search result!!\n");
}


void SearchReservationField(Reserve *r[], int count) { // ���� ���
    int flag = 0;
    int field_num;
    char search_name[30];
    printf("ã�� ���� ��Ҹ� �Է��Ͻÿ�. : 1. ����ʵ�, 2. ����ũǲ����");
    scanf("%d", &field_num);
    if(field_num == 1){
        strcpy(search_name, "PyeongBong_Field");
    }
    else if(field_num == 2){
        strcpy(search_name, "Hiddink_Futsal_Field");
    }
    printf("\n��ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
    for(int i=0; i<count; i++){
        if(strstr(r[i]->field, search_name)){//�̸��� ã�Ҵٸ�
            printf(" %d%10s\t%10s\t (", i+1, r[i]->field, fieldName[r[i]->field]);
            PrintDateTime(&r[i]->startTime);
            printf(" ~ ");
            PrintDateTime(&r[i]->endTime);
            printf(")\n");
            flag++;
        }
    }
    if(flag == 0) printf("\t\t!!No search result!!\n");
}


// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count) { // ���� �Է�
}

int SaveAsFile(char *filename, Reserve *r[], int count) { // ���� ���
}

#endif