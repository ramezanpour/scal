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

#include "convertor.h"

date jalali_to_gregorian(int d, int m, int y)
{
    int sumshamsi[] = {31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 365};
    int miladidays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int yy, mm, daycount;
    daycount = d;
    if (m > 1)
        daycount = daycount + sumshamsi[m - 2];
    yy = y + 621;
    daycount = daycount + 79;
    if (is_leap(yy))
    {
        if (daycount > 366)
        {
            daycount -= 366;
            yy++;
        }
    }
    else if (daycount > 365)
    {
        daycount -= 365;
        yy++;
    }
    if (is_leap(yy))
        miladidays[1] = 29;
    mm = 0;
    while (daycount > miladidays[mm])
    {
        daycount = daycount - miladidays[mm];
        mm++;
    }
    date gregorianDate;
    gregorianDate.year = yy;
    gregorianDate.month = (mm + 1);
    gregorianDate.day = daycount;
    return gregorianDate;
}

date gregorian_to_jalali(int day, int month, int year)
{

    int j_day, j_month, j_year;
    int day_count, farvardin_day_diff, dey_day_diff;
    int sumDayMiladiMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int sumDayMiladiMonthLeap[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    date j_date;

    farvardin_day_diff = 79;

    if (is_leap(year))
    {
        day_count = sumDayMiladiMonthLeap[month - 1] + day;
    }
    else
    {
        day_count = sumDayMiladiMonth[month - 1] + day;
    }
    if ((is_leap(year - 1)))
    {
        dey_day_diff = 11;
    }
    else
    {
        dey_day_diff = 10;
    }
    if (day_count > farvardin_day_diff)
    {
        day_count = day_count - farvardin_day_diff;
        if (day_count <= 186)
        {
            switch (day_count % 31)
            {
            case 0:
                j_month = day_count / 31;
                j_day = 31;
                break;
            default:
                j_month = (day_count / 31) + 1;
                j_day = (day_count % 31);
                break;
            }
            j_year = year - 621;
        }
        else
        {
            day_count = day_count - 186;
            switch (day_count % 30)
            {
            case 0:
                j_month = (day_count / 30) + 6;
                j_day = 30;
                break;
            default:
                j_month = (day_count / 30) + 7;
                j_day = (day_count % 30);
                break;
            }
            j_year = year - 621;
        }
    }
    else
    {
        day_count = day_count + dey_day_diff;

        switch (day_count % 30)
        {
        case 0:
            j_month = (day_count / 30) + 9;
            j_day = 30;
            break;
        default:
            j_month = (day_count / 30) + 10;
            j_day = (day_count % 30);
            break;
        }
        j_year = year - 622;
    }
    j_date.year = j_year;
    j_date.month = j_month;
    j_date.day = j_day;

    return j_date;
}

int is_leap(int year)
{
    if (((year % 100) != 0 && (year % 4) == 0) || ((year % 100) == 0 && (year % 400) == 0))
        return 1;
    else
        return 0;
}

char *get_month_name(int j_month)
{
    switch (j_month)
    {
    case 1:
        return "Farvardin";
    case 2:
        return "Ordibehesht";
    case 3:
        return "Khordad";
    case 4:
        return "Tir";
    case 5:
        return "Mordad";
    case 6:
        return "Shahrivar";
    case 7:
        return "Mehr";
    case 8:
        return "Aban";
    case 9:
        return "Azar";
    case 10:
        return "Day";
    case 11:
        return "Bahman";
    case 12:
        return "Esfand";
    default:
        return "Unknown";
    }
}

int get_day_of_week(int g_day, int g_month, int g_year)
{
    return (g_day += g_month < 3 ? g_year-- : g_year - 2, 23 * g_month / 9 + g_day + 4 + g_year / 4 - g_year / 100 + g_year / 400) % 7;
}

char *get_day_of_week_name(int dow)
{
    switch (dow)
    {
    case 0:
        return "Sunday";
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    default:
        return "Unknow";
    }
}
