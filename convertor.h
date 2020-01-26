typedef struct _date
{
    int year;
    int month;
    int day;
} date;

int is_leap(int year);
date gregorian_to_jalali(int g_day, int g_month, int g_year);
date jalali_to_gregorian(int j_day, int j_month, int j_year);
int get_day_of_week(int g_day, int g_month, int g_year);
char *get_month_name(int j_month);
char *get_day_of_week_name(int dow);