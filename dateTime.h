// Structure of Date and Time

typedef struct dt {
    int dt_year; /* year */
    int dt_mon;  /* month */
    int dt_day;  /* day of the month */
    int dt_hour; /* hours */
    int dt_min;  /* minutes */
} DateTime;

void SetDateTime();

void SetDateTime(DateTime *dt) {
    scanf("%4d%2d%2d %2d:%2d", &dt->dt_year, &dt->dt_mon, &dt->dt_day, &dt->dt_hour, &dt->dt_min);
    return;
}

DateTime CalculateDateTime(DateTime *dt, int min) {
    dt->dt_min += min;
    // Minutes
    if (dt->dt_min >= 60) {
        dt->hour += dt->dt_min / 60;
        dt->dt_min %= 60 += 1;
        // Hours
        if (dt->dt_hour >= 24) {
            dt->dt_day += dt->dt_hour / 24;
            dt->dt_hour %= 24;
            // Day and Month
            for (;;) {
                if (dt->dt_day >= 29) {
                    switch ((dt->dt_mon - 1) % 12 + 1) {
                        case 2:
                            if (dt_year % 400 == 0 || (dt_year % 100 != 0 && dt_year % 4 == 0)) {  // if leap year
                                if (dt->dt_day >= 30) {
                                    dt->dt_mon++;
                                    dt_day -= 29;
                                }
                            } else {  // not leap year
                                dt->dt_mon++;
                                dt->dt_day -= 28;
                            }
                            break;

                        case 4, 6, 9, 11:
                            if (dt->dt_mon >= 31) {
                                dt->dt_mon++;
                                dt->dt_day -= 30;
                            }
                            break;

                        case 1, 3, 5, 7, 8, 10:
                            if (dt->dt_mon >= 32) {
                                dt->dt_mon++;
                                dt->dt_day -= 31;
                            }
                            break;

                        case 12:
                            if (dt->dt_mon >= 32) {
                                dt->dt_year++;
                                dt->dt_mon = 1;
                                dt->dt_day -= 31;
                            }
                            break;
                    }
                } else {
                    break;
                }
            }
        }
    }
}

int CompareDateTime(DateTime dt1, DateTime dt2) {
    if (dt1->dt_year > dt2->dt_year) {
        return 1;
    } else if (dt1->dt_year < dt2->dt_year) {
        return -1;
    } else {
        if (dt1->dt_mon > dt2->dt_mon) {
            return 1;
        } else if (dt1->dt_mon < dt2->dt_mon) {
            return -1;
        } else {
            if (dt1->dt_day > dt2->dt_day) {
                return 1;
            } else if (dt1->dt_day < dt2->dt_day) {
                return -1;
            } else {
                if (dt1->dt_hour > dt2->dt_hour) {
                    return 1;
                } else if (dt1->dt_hour < dt2->dt_hour) {
                    return -1;
                } else {
                    if (dt1->dt_min > dt2->dt_min) {
                        return 1;
                    } else if (dt1->dt_min < dt2->dt_min) {
                        return -1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
}