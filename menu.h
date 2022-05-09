#ifndef __menu_H__
#define __menu_H__

#include <stdio.h>

// Menu Functions
#define N_MENU 7

enum Menu {
    QUIT,
    LIST,
    CREATE,
    SEARCH,
    LOAD,
    SAVE
};


void printMenu() {
    printf("\n");
    printf("[메뉴]\n");
    printf("1. 예약 목록\n");
    printf("2. 예약 추가\n");
    printf("3. 예약 수정\n");
    printf("4. 예약 삭제\n");
    printf("5. 예약 검색\n");
    printf("6. 예약 목록 불러오기\n");
    printf("7. 예약 목록 저장\n");
    printf("0. 종료\n");
}

enum Menu chooseMenu() {
    enum Menu menu;
    for (;;) {
        printMenu();
        printf("-----------------\n");
        printf("메뉴를 입력하시오: ");
        scanf("%d", &menu);

        if (menu >= 0 && menu <= 7)
            return menu;
        else
            printf("잘못된 입력!\n");
    }
}

#endif