#include<stdio.h>
#include<stdlib.h>

struct Process
{
    int AT, BT, FT, TAT, WT, id;
    int RBT; // Remaining Burst Time
    int arrived;
    int completed;
};
void SortByAT(struct Process *process, int length)
{
    int swapped = 0;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (process[j].AT > process[j + 1].AT)
            {
                // printf("\n\t %d and %d",process[j].AT,process[j + 1].AT);
                swapped = 1;
                struct Process temp;
                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}


int getNextIndx(struct Process *p, int length, int prevIndx, int ctime)
{
    int i = prevIndx;
    do
    {
        i = (i + 1) % length;
    } while (!(p[i].completed == 0 && p[i].AT <= ctime));

    return i;
}


void round_robin(){
    printf("Round Robin Scheduling\n");

    int np;
    printf("\n\t\ No. of processes:");
    scanf("%d", &np);
    struct Process *process = (struct Process *)calloc(np, sizeof(struct Process));

    for (int i = 0; i < np; i++)
    {
        printf("For Process P%d:\n\tArrival time:", i + 1);
        scanf("%d", &process[i].AT);
        printf("\t Burst Time:");
        scanf("%d", &process[i].BT);
        process[i].RBT = process[i].BT;
        process[i].id = i;
        process[i].arrived = 0;
        process[i].completed = 0;
    }

    printf("\n\tOver Head Time: ");
    int overheadTime;
    scanf("%d", &overheadTime);

    printf("\n\tTime Quantum: ");
    int time_slice;
    scanf("%d", &time_slice);

    SortByAT(process, np);

    int ctime = 0, cprocessIndx = -1, cprocessRBT = 0, processCount = 0, cSliceCounter = time_slice;
    while (processCount != np)
    {
        if (process[0].AT <= ctime)
        {
            if (cprocessIndx == -1)
            { // No process selected
                cprocessIndx = 0;
                cprocessRBT = process[cprocessIndx].RBT;
                processCount++;
            }

            if (cprocessRBT == 0)
            {
                // Process completed.

                // Fill the process data
                process[cprocessIndx].FT = ctime;
                process[cprocessIndx].TAT = process[cprocessIndx].FT - process[cprocessIndx].AT;
                process[cprocessIndx].WT = process[cprocessIndx].TAT - process[cprocessIndx].BT;
                process[cprocessIndx].completed = 1;

                processCount++;

                // switch Process
                ctime += overheadTime;

                cprocessIndx = getNextIndx(process, np, cprocessIndx, ctime);
                cprocessRBT = process[cprocessIndx].RBT;
                cSliceCounter = time_slice;
            }

            if (cSliceCounter == 0)
            {
                // switch Process
                int nextIndx = getNextIndx(process, np, cprocessIndx, ctime);
                if (nextIndx != cprocessIndx)
                {
                    ctime += overheadTime;

                    cprocessIndx = nextIndx;
                }
                cprocessRBT = process[cprocessIndx].RBT;
                cSliceCounter = time_slice;
            }

            cSliceCounter--;
            cprocessRBT--;
            process[cprocessIndx].RBT--;
            printf("\n %2d |  P%d  |   %2d  ", ctime, process[cprocessIndx].id, process[cprocessIndx].RBT);
        }
        ctime++;
        // printf("\n\t\t\t\t%d", processCount);
        }
        // calculate the average TAT and WT
        float avgTAT = 0, avgWT = 0;
        for (int i = 0; i < np; i++)
        {
            avgTAT += process[i].TAT;
            avgWT += process[i].WT;
        }
        avgTAT /= np;
        avgWT /= np;

        printf("\n  Average Turn Around Time: %f", avgTAT);
        printf("\n  Average Waiting Time: %f", avgWT);

        printf("\n\n Process\tAT\tBT\tFT\tTAT\tWT");
        for (int i = 0; i < np; i++)
        {
            printf("\n P%d\t\t%d\t%d\t%d\t%d\t%d", process[i].id, process[i].AT, process[i].BT, process[i].FT, process[i].TAT, process[i].WT);
        }

        printf("\n\n");
        

        
    }


int main()
{
    round_robin();
    return 0;
}
