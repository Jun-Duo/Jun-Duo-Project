#include <stdbool.h>
#include <stdio.h>

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
    scanf("%04d%02d%02d %02d:%02d", &dt->dt_year, &dt->dt_mon, &dt->dt_day, &dt->dt_hour, &dt->dt_min);
}

void PrintDateTime(DateTime *dt) {
    printf("%04d%02d%02d %02d:%02d", dt->dt_year, dt->dt_mon, dt->dt_day, dt->dt_hour, dt->dt_min);
}

void CopyDateTime(DateTime *dt1, DateTime *dt2) {
    dt1->dt_year = dt2->dt_year;
    dt1->dt_mon = dt2->dt_mon;
    dt1->dt_day = dt2->dt_day;
    dt1->dt_hour = dt2->dt_hour;
    dt1->dt_min = dt2->dt_min;
}

bool IsValidTime(DateTime *dt) {
    if (dt->dt_hour >= 0 && dt->dt_hour < 24) {
        if (dt->dt_min >= 0 && dt->dt_min < 60) {
            return true;
        }
    }
    return false;
}

bool IsValidDate(DateTime *dt) {
    if (dt->dt_mon >= 1 && dt->dt_mon <= 12) {
        if (dt->dt_day >= 0) {
            switch (dt->dt_mon) {
                case 2:
                    if (dt->dt_year % 400 == 0 || (dt->dt_year % 100 != 0 && dt->dt_year % 4 == 0)) {  // if leap year
                        if (dt->dt_day <= 29) {
                            return true;
                        } else
                            return false;
                    } else {  // not leap year
                        if (dt->dt_day <= 28) {
                            return true;
                        } else
                            return false;
                    }
                    break;

                case 4:
                case 6:
                case 9:
                case 11:
                    if (dt->dt_day <= 30) {
                        return true;
                    } else
                        return false;
                    break;

                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (dt->dt_day <= 31) {
                        return true;
                    } else
                        return false;
                    break;
            }
        } else
            return false;
    } else
        return false;
}

void CalculateDateTime(DateTime *res, DateTime *dt, int min) {
    CopyDateTime(res, dt);
    res->dt_min += min;
    // Minutes
    if (res->dt_min >= 60) {
        res->dt_hour += res->dt_min / 60;
        res->dt_min %= 60;
        // Hours
        if (res->dt_hour >= 24) {
            res->dt_day += res->dt_hour / 24;
            res->dt_hour %= 24;
            // Day and Month
            for (;;) {
                if (res->dt_day >= 29) {
                    switch ((res->dt_mon - 1) % 12 + 1) {
                        case 2:
                            if (res->dt_year % 400 == 0 || (res->dt_year % 100 != 0 && res->dt_year % 4 == 0)) {  // if leap year
                                if (res->dt_day >= 30) {
                                    res->dt_mon++;
                                    res->dt_day -= 29;
                                }
                            } else {  // not leap year
                                res->dt_mon++;
                                res->dt_day -= 28;
                            }
                            break;

                        case 4:
                        case 6:
                        case 9:
                        case 11:
                            if (res->dt_mon >= 31) {
                                res->dt_mon++;
                                res->dt_day -= 30;
                            }
                            break;

                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                            if (res->dt_mon >= 32) {
                                res->dt_mon++;
                                res->dt_day -= 31;
                            }
                            break;

                        case 12:
                            if (res->dt_mon >= 32) {
                                res->dt_year++;
                                res->dt_mon = 1;
                                res->dt_day -= 31;
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

int CompareDateTime(DateTime *dt1, DateTime *dt2) {
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