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
    printf("[�޴�]\n");
    printf("1. ���� ���\n");
    printf("2. ���� �߰�\n");
    printf("3. ���� ����\n");
    printf("4. ���� ����\n");
    printf("5. ���� �˻�\n");
    printf("6. ���� ��� �ҷ�����\n");
    printf("7. ���� ��� ����\n");
    printf("0. ����\n");
}

enum Menu chooseMenu() {
    enum Menu menu;
    for (;;) {
        printMenu();
        printf("-----------------\n");
        printf("�޴��� �Է��Ͻÿ�: ");
        scanf("%d", &menu);

        if (menu >= 0 && menu <= 7)
            return menu;
        else
            printf("�߸��� �Է�!\n");
    }
}

#endif