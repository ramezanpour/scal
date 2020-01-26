#include <stdio.h>
#include <time.h>
#include "convertor.h"

void draw_cal(int d, int m, int y)
{
    date shamshiDate = gregorian_to_jalali(d, m, y);
    date first_day_of_month_greorian_date = jalali_to_gregorian(1, shamshiDate.month, shamshiDate.year);
    int first_day_of_month_week = get_day_of_week(first_day_of_month_greorian_date.day,
                                                  first_day_of_month_greorian_date.month,
                                                  first_day_of_month_greorian_date.year);

    int month_len = shamshiDate.month < 6 ? 31 : 30;
    if (is_leap(y) && shamshiDate.month == 12)
    {
        month_len = 30;
    }

    // Print month and year
    printf("%s %d\n", get_month_name(shamshiDate.month), shamshiDate.year);
    // Print headers
    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
    for (int i = 0; i < first_day_of_month_week; i++)
    {
        printf("\t");
    }
    for (int i = 1; i <= month_len; i++)
    {
        if (i == shamshiDate.day)
        {
            printf("\033[1;30m");
            printf("\033[1;47m");
        }
        printf("%d\t", i);
        if (i == shamshiDate.day)
        {
            printf("\033[0m");
        }
        if ((first_day_of_month_week + i) % 7 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    draw_cal(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return 0;
}
