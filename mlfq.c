// MULTI-LEVEL FEEDBACK QUEUE

#include <stdio.h>
#include <stdlib.h>

#define CT 100

typedef struct {
    int id;
    int duration;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct {
    Process *processes[CT];
    int front, rear;
    int time_quantum;
} Queue;

void initializeQueue(Queue *q, int time_quantum)
{
    q->front = q->rear = -1;
    q->time_quantum = time_quantum;
}

void enqueue(Queue *q, Process *p)
{
    if (q->rear == CT - 1)
    {
        printf("Queue is full!\n");
        return;
    }
    q->processes[++q->rear] = p;
    if (q->front == -1)
    {
        q->front = 0;
    }
    printf("Process %d enqueued in queue with time quantum %d\n", p->id, q->time_quantum);

}

Process* dequeue(Queue *q)
{
    if (q->front == -1)
    {
        return NULL;
    }
    Process *p = q->processes[q->front];
    if (q->front == q->rear)
    {
        q->front = q->rear = -1;
    }
    else
    {
        q->front++;
    }
    printf("Process %d dequeued from queue with time quantum %d\n", p->id, q->time_quantum);
    return p;
}

void mlfq_scheduling(Queue *q0, Queue *q1, Queue *q2)
{
    int total_time = 0;
    while (1)
    {
        Process *p = dequeue(q0);
        if (p != NULL)
        {
            printf("Process %d is running in high priority queue\n", p->id);
            if (p->remaining_time <= q0->time_quantum)
            {
                total_time += p->remaining_time;
                p->remaining_time = 0;
                p->waiting_time = total_time - p->duration;
                p->turnaround_time = total_time;
                printf("Process %d finished execution\n", p->id);
            }
            else
            {
                p->remaining_time -= q0->time_quantum;
                total_time += q0->time_quantum;
                enqueue(q1, p);
            }
            continue;
        }
        
        p = dequeue(q1);
        if (p != NULL)
        {
            printf("Process %d is running in medium priority queue\n", p->id);
            if (p->remaining_time <= q1->time_quantum)
            {
                total_time += p->remaining_time;
                p->remaining_time = 0;
                p->waiting_time = total_time - p->duration;
                p->turnaround_time = total_time;
                printf("Process %d finished execution\n", p->id);
            }
            else
            {
                p->remaining_time -= q1->time_quantum;
                total_time += q1->time_quantum;
                enqueue(q2, p);
            }
            continue;
        }

        p = dequeue(q2);
        if (p != NULL)
        {
            printf("Process %d is running in low priority queue\n", p->id);
            if (p->remaining_time <= q2->time_quantum)
            {
                total_time += p->remaining_time;
                p->remaining_time = 0;
                p->waiting_time = total_time - p->duration;
                p->turnaround_time = total_time;
                printf("Process %d finished execution\n", p->id);
            }
            else
            {
                p->remaining_time -= q2->time_quantum;
                total_time += q2->time_quantum;
                enqueue(q2, p);
            }
            continue;
        }

        break;
    }
}

int main()
{
    Queue q0, q1, q2;
    initializeQueue(&q0, 2);
    initializeQueue(&q1, 4);
    initializeQueue(&q2, 8);

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n > CT) { n = CT; }

    Process *processes = (Process *) malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++)
    {
        printf("Enter duration for process %d: ", i+1);
        scanf("%d", &processes[i].duration);
        processes[i].id = i+1;
        processes[i].remaining_time = processes[i].duration;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        enqueue(&q0, &processes[i]);
    }

    mlfq_scheduling(&q0, &q1, &q2);

    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].duration, processes[i].waiting_time, processes[i].turnaround_time);
    }

    return 0;
}