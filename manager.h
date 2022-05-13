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
    printf("����");
    getchar();
    printf("ã�� �������� �Է��� �Է��Ͻÿ�. : ");
    fgets(search_name,30,stdin);
    printf("�Ϸù�ȣ  �����ڸ�\t �����ʵ�\t ����ð�\n");
    for(int i=0; i<count; i++){
        if(strstr(r[i]->name,search_name)){//�̸��� ã�Ҵٸ�
            printf("%10s\t\t%10s\t (", r[i]->name, fieldName[r[i]->field]);
            PrintDateTime(&r[i]->startTime);
            printf(" ~ ");
            PrintDateTime(&r[i]->endTime);
            printf(")\n");
            flag++;
        }
    }
    if(flag == 0) printf("No search result!!\n");
}

void SearchReservationDate(Reserve *r[], int count) { // ���� ��¥
    printf("1.");
}

void SearchReservationTime(Reserve *r[], int count) { // ���� �ð�
printf("1.");
}

void SearchReservationField(Reserve *r[], int count) { // ���� ���
printf("1.");
}


// File I/O Functions
int LoadFromFile(char *filename, Reserve *r[], int *count) { // ���� �Է�
}

int SaveAsFile(char *filename, Reserve *r[], int count) { // ���� ���
}

#endif