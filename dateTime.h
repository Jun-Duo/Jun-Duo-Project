#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define TIME_STR_LEN 8 + 1 + 5 + 1
// Structure of Date and Time
typedef struct dt {
    int dt_year; /* year */
    int dt_mon;  /* month */
    int dt_day;  /* day of the month */
    int dt_hour; /* hours */
    int dt_min;  /* minutes */
} DateTime;

/*
    Function Declarations
    */
void SetDateTime(DateTime *dt);
void SetDate(DateTime *dt);
void SetTime(DateTime *dt);
void PrintDateTime(DateTime *dt);
void CopyDateTime(DateTime *dt1, DateTime *dt2);
bool IsValidTime(DateTime *dt);
bool IsValidDate(DateTime *dt);
bool IsFutureDateTime(DateTime *dt);
void CalculateDateTime(DateTime *res, DateTime *dt, int min);
int CompareDateTime(DateTime *dt1, DateTime *dt2);
int CompareDate(DateTime *dt1, DateTime *dt2);
int CompareTime(DateTime *dt1, DateTime *dt2);

/*
    Function Definitions
*/
// stdin to dateTime
void SetDateTime(DateTime *dt) {
    scanf("%04d%02d%02d %02d:%02d", &dt->dt_year, &dt->dt_mon, &dt->dt_day, &dt->dt_hour, &dt->dt_min);
}

// stdin to dateTime (only date)
void SetDate(DateTime *dt) {
    scanf("%04d%02d%02d", &dt->dt_year, &dt->dt_mon, &dt->dt_day);
}

// stdin to dateTime (only time)
void SetTime(DateTime *dt) {
    scanf("%02d:%02d", &dt->dt_hour, &dt->dt_min);
}

// Print dateTime
void PrintDateTime(DateTime *dt) {
    printf("%04d%02d%02d %02d:%02d", dt->dt_year, dt->dt_mon, dt->dt_day, dt->dt_hour, dt->dt_min);
}

// Copy dateTime
void CopyDateTime(DateTime *dt1, DateTime *dt2) {
    dt1->dt_year = dt2->dt_year;
    dt1->dt_mon = dt2->dt_mon;
    dt1->dt_day = dt2->dt_day;
    dt1->dt_hour = dt2->dt_hour;
    dt1->dt_min = dt2->dt_min;
}

// check if Time is Valid
bool IsValidTime(DateTime *dt) {
    if (dt->dt_hour >= 0 && dt->dt_hour < 24) {
        if (dt->dt_min >= 0 && dt->dt_min < 60) {
            return true;
        }
    }
    return false;
}

// check if Date is Valid
bool IsValidDate(DateTime *dt) {
    if (dt->dt_mon >= 1 && dt->dt_mon <= 12) {
        if (dt->dt_day >= 0) {
            switch (dt->dt_mon) {
                case 2: // 28 (non leap year) or 29 (leap year)
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

                case 4: // 30
                case 6:
                case 9:
                case 11:
                    if (dt->dt_day <= 30) {
                        return true;
                    } else
                        return false;
                    break;

                case 1: // 31
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

// check if dateTime is a future date time
bool IsFutureDateTime(DateTime *dt) {
    time_t now_t, reserve_t;
    struct tm nowTime, reserveTime;

    reserveTime.tm_year = dt->dt_year - 1900;
    reserveTime.tm_mon = dt->dt_mon - 1;
    reserveTime.tm_mday = dt->dt_day;
    reserveTime.tm_hour = dt->dt_hour;
    reserveTime.tm_min = dt->dt_min;
    reserveTime.tm_sec = 0;

    reserve_t = mktime(&reserveTime);

    // get now time
    time(&now_t);
    nowTime = *localtime(&now_t);

    // calculate time difference
    double diff_t = difftime(reserve_t, now_t);

    if (diff_t > 0) // if reserveTime is later than nowTime
        return true;
    else
        return false;
}

// Calculate dateTime + min
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
                        case 2: // 28 (non leap year) or 29 (leap year)
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

                        case 4: // 30
                        case 6:
                        case 9:
                        case 11:
                            if (res->dt_mon >= 31) {
                                res->dt_mon++;
                                res->dt_day -= 30;
                            }
                            break;

                        case 1: // 31
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

                        case 12: // 31 and last month of year
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

// compare two dateTime objects and return what is later
int CompareDateTime(DateTime *dt1, DateTime *dt2) {
    // year
    if (dt1->dt_year > dt2->dt_year) {
        return 1; // dt1 is later than dt2
    } else if (dt1->dt_year < dt2->dt_year) {
        return -1; // dt2 is later than dt1
    } else {
        // month
        if (dt1->dt_mon > dt2->dt_mon) {
            return 1;
        } else if (dt1->dt_mon < dt2->dt_mon) {
            return -1;
        } else {
            // day
            if (dt1->dt_day > dt2->dt_day) {
                return 1;
            } else if (dt1->dt_day < dt2->dt_day) {
                return -1;
            } else {
                // hour
                if (dt1->dt_hour > dt2->dt_hour) {
                    return 1;
                } else if (dt1->dt_hour < dt2->dt_hour) {
                    return -1;
                } else {
                    // minute
                    if (dt1->dt_min > dt2->dt_min) {
                        return 1;
                    } else if (dt1->dt_min < dt2->dt_min) {
                        return -1;
                    } else {
                        return 0; // exactly same
                    }
                }
            }
        }
    }
}

// compare two dateTime objects (only date)
int CompareDate(DateTime *dt1, DateTime *dt2) {
    // year
    if (dt1->dt_year > dt2->dt_year) {
        return 1; // dt1 is later than dt2
    } else if (dt1->dt_year < dt2->dt_year) {
        return -1; // dt2 is later than dt1
    } else {
        // month
        if (dt1->dt_mon > dt2->dt_mon) {
            return 1;
        } else if (dt1->dt_mon < dt2->dt_mon) {
            return -1;
        } else {
            // day
            if (dt1->dt_day > dt2->dt_day) {
                return 1;
            } else if (dt1->dt_day < dt2->dt_day) {
                return -1;
            } else {
                return 0; // dt1 and dt2 are in the same day
            }
        }
    }
}

// compare two dateTime objects (only time)
int CompareTime(DateTime *dt1, DateTime *dt2) {
    // hour
    if (dt1->dt_hour > dt2->dt_hour) {
        return 1; // dt1 is later than dt2
    } else if (dt1->dt_hour < dt2->dt_hour) {
        return -1; // dt2 is later than dt1
    } else {
        // minute
        if (dt1->dt_min > dt2->dt_min) {
            return 1;
        } else if (dt1->dt_min < dt2->dt_min) {
            return -1;
        } else {
            return 0; // dt1's time and dt2's time are same
        }
    }
}