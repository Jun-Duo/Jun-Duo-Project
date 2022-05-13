#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "manager.h"
#include "menu.h"
#include "reserve.h"

#define MAX_N 100

int main() {
    // Memory Allocation
    Reserve **r = (Reserve **)malloc(MAX_N * sizeof(Reserve *));
    for (int i = 0; i < MAX_N; i++) {
        r[i] = (Reserve *)malloc(MAX_N * sizeof(Reserve));
    }

    int cnt = 0;
    bool stop = false;
    while (!stop && cnt < MAX_N) {
        enum Menu menu = chooseMenu();
        switch (menu) {
            case LIST:
                ListReservation(r, cnt);
                break;
            case CREATE:
                CreateReservation(r, &cnt, MAX_N);
                break;
            case UPDATE:
                UpdateReservation(r, cnt);
                break;
            case DELETE:
                DeleteReservation(r, &cnt);
                break;
            case SEARCH:
                SearchReservation(r, cnt);
                break;
            case LOAD:
                LoadFromFile(r, &cnt, MAX_N);
                break;
            case SAVE:
                SaveAsFile(r, cnt);
                break;
            case QUIT:
                stop = true; // make stop
                // Memory Deallocation
                for (int i = 0; i < MAX_N; i++) {
                    free(r[i]);
                }
                free(r);
                break;
        }
    }
    return 0;
}