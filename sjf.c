// SHORTEST JOB FIRST

#include <stdio.h>

#define CT 100

int main()
{
    int n;
    int duration[CT], waiting_time[CT], turnaround_time[CT], pid[CT];
    float total_waiting_time, total_turnaround_time;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n > CT) { n = CT; }

    for (int i = 0; i < n; i++)
    {
        printf("Enter execution time for process %d: ", i+1);
        scanf("%d", &duration[i]);
        pid[i] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (duration[j] > duration[j+1])
            {
                int tmp;

                tmp  = duration[j];
                duration[j] = duration[j+1];
                duration[j+1] = tmp;

                tmp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = tmp;
            }
        }
    }

    waiting_time[0] = 0;
    total_waiting_time = waiting_time[0];
    turnaround_time[0] = duration[0];
    total_turnaround_time = turnaround_time[0];
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = duration[i-1] + waiting_time[i-1];
        total_waiting_time += waiting_time[i];

        turnaround_time[i] = duration[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Process\tExecution Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", pid[i], duration[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time/n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time/n);

    return 0;
}
