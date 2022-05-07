#include <stdio.h>
#include <stdlib.h>

#include "reserve.h"
#include "manager.h"
#include "menu.h"

#define MAX_N 100

int main() {

    Reserve **p = (Reserve **)malloc(MAX_N * sizeof(Reserve *));
    for (int i = 0; i < 100; i++) {
        p[i] = (Reserve *)malloc(MAX_N * sizeof(Reserve));
    }

    int cnt = 0;
    int stop = 0;
    while (!stop && cnt < MAX_N) {
        enum Menu menu = chooseMenu();
        switch (menu) {
            case LIST:
                ListReservation(p, cnt);
                break;
            case CREATE:
                CreateReservation(p[cnt]);
                cnt++;
                break;
            case SEARCH:
                SearchReservation(p, cnt);
                break;
            case LOAD:
                LoadFromFile("input.txt", p, &cnt);
                break;
            case SAVE:
                SaveAsFile("output.txt", p, cnt);
                break;
            case QUIT:
                stop = 1;
                break;
        }
    }
    return 0;
}