#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// day_of_year = md_to_yd
// month_day   = yd_to_md

// Returns whether `year` is a leap year.
int is_leap(int year);

// Converts `month` of the `day` to the `day` of the `year`.
int md_to_yd(int year, int month, int day);

// Converts `day` of the `year` to the month of the `day` by putting those into `pmonth` and `pday`.
void yd_to_md(int year, int day, int *pmonth, int *pday);

// Returns the name of the `n`th month.
char *month_name(int n);

char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int is_leap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int md_to_yd(int year, int month, int day) {
    int leap = is_leap(year);

    assert(month >= 1 && month <= 12 && day >= 1 && day <= 31);

    for (int i = 1; i < month; i++) {
        day += *(*(daytab + leap) + i);
    }
    return day;
}

void yd_to_md(int year, int day, int *pmonth, int *pday) {
    int i, leap = is_leap(year);

    assert(day >= 1 && day <= 366);

    for (i = 1; day > *(*(daytab + leap) + i); i++) {
        day -= *(*(daytab + leap) + i);
    }

    *pmonth = i;
    *pday = day;
}

char *month_name(int n) {
    static char *name[] = {
        "Illegal month", "January", "February",
        "March", "April", "May", "June", "July",
        "August", "September", "October", "November",
        "December",
    };

    return (n >= 1 && n <= 12) ? name[n] : name[0];
}

int main(void) {
    int a, b;
    yd_to_md(2025, 182, &a, &b);
    printf("Hello from %s %i and counting!\n", month_name(a), b);
}

/*
508: There is no error checking in `day_of_year` or `month_day`.
     Remedy this defect.
509: Rewrite the routines `day_of_year` and `month_day` with pointers
     instead of indexing.
*/