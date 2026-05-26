#include <stdio.h>

typedef struct {
    int hour;
    int minute;
    int second;
} Time;

void PrintTime(Time time)
{
    printf("%02d:%02d:%02d", time.hour, time.minute, time.second);
}

Time IncTime(Time time, int seconds)
{
    int total = time.hour * 3600 + time.minute * 60 + time.second + seconds;
    int day = 24 * 3600;
    total %= day;
    if (total < 0)
        total += day;
    time.hour = total / 3600;
    total %= 3600;
    time.minute = total / 60;
    time.second = total % 60;
    return time;
}

int CmpTime(Time time1, Time time2)
{
    int t1 = time1.hour * 3600 + time1.minute * 60 + time1.second;
    int t2 = time2.hour * 3600 + time2.minute * 60 + time2.second;
    if (t1 < t2)
        return -1;
    if (t1 > t2)
        return 1;
    return 0;
}

void SwapTime(Time *time1, Time *time2)
{
    Time temp = *time1;
    *time1 = *time2;
    *time2 = temp;
}


int main(void){
    Time time1 = {16, 34, 12};
    Time time2 = {6, 8, 15};

    printf("Time1: ");
    PrintTime(time1);
    printf("\n");

    printf("Time2: ");
    PrintTime(time2);
    printf("\n");

    Time incTime1 = IncTime(time1, 20);
    printf("IncTime1: ");
    PrintTime(incTime1);
    printf("\n");

    int cmp = CmpTime(time1, time2);
    if (cmp < 0)
        printf("Time1 is earlier than Time2\n");
    else if (cmp > 0)
        printf("Time1 is later than Time2\n");
    else
        printf("Time1 and Time2 are the same\n");

    SwapTime(&time1, &time2);
    printf("After swapping:\n");
    printf("Time1: ");
    PrintTime(time1);
    printf("\n");
    printf("Time2: ");
    PrintTime(time2);
    printf("\n");
    return 0;
}