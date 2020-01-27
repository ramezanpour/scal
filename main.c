// The MIT License (MIT)

// Copyright (c) 2020 Mohammad Mahdi Ramezanpour

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "convertor.h"

#define VERSION "0.0.1"

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

bool has_flag(const char *flag, const char *argv[], int argc)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], flag) == 0)
            return true;
    }
    return false;
}

const char *get_option_value(const char *option, const char *argv[], int argc)
{
    int option_index = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], option) == 0)
            option_index = i;
    }

    if (option_index == 0)
        return "";
    else
        return (option_index + 1 > argc) ? "" : argv[option_index + 1];
}

int main(int argc, char const *argv[])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (argc == 1)
    {
        draw_cal(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        return 0;
    }
    else
    {
        if (has_flag("--version", argv, argc))
        {
            printf("SCAL Version %s\n", VERSION);
            return 0;
        }
        if (has_flag("--simple", argv, argc))
        {
            // Return a simple date
            date current_shami_date = gregorian_to_jalali(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            char *format = "%d-%02d-%02d";

            // Support for custom format
            if (has_flag("--format", argv, argc))
            {
                const char *custom_format = get_option_value("--format", argv, argc);
                if (strcmp(custom_format, "") != 0)
                {
                    format = malloc(sizeof(char) * strlen(custom_format));
                    strcpy(format, custom_format);
                }
            }
            printf(format,
                   current_shami_date.year,
                   current_shami_date.month,
                   current_shami_date.day);

            printf("\n");
            return 0;
        }
    }
}
