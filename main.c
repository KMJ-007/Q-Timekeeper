#include<stdio.h>
#include"qtimekeeper.h"
// #include"ganttchart.h"

int main()
{
    printf("\nWelcome to Q-Timekepper \n");
    printf("job scheduling simulator \n");
    // qtimekeeper();
    process_t processes[] = {
        {1, 0, 5, 1, 0, 5, 0, 0},
        {2, 2, 3, 2, 0, 3, 0, 0},
        {3, 3, 1, 3, 0, 1, 0, 0},
        {4, 5, 2, 4, 0, 2, 0, 0},
        {5, 6, 4, 5, 0, 4, 0, 0},
    };
    draw_gantt_chart(processes, 5, 10,100,100);

    return 0;
}
