#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSES 20
#define MIN_PROCESSES 5
#define MAX_ARRIVE_TIME 10
#define MAX_BURST_TIME 10

struct process{
    int arrive_time;
    int burst_time;
    int completion_time;
    int wait_time;
    int turnaround_time;
};

int main(int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    int n = 0;
    int random = 0;
    char generate[20] = "n";
    struct process procs[MAX_PROCESSES];

    printf("Generate input randomly? [y/n]: ");
    scanf("%s", generate);

    if ( strcmp(generate, "y") == 0 || strcmp(generate, "Y") == 0 ){
        random = 1;
        n = rand() % (MAX_PROCESSES-MIN_PROCESSES) + MIN_PROCESSES;
        printf("Number of processes: %d\n", n);
    }
    else{
        printf("Number of processes: ");
        scanf("%d", &n);
    }

    for (int i = 0; i < n; ++i){
        if ( random ) {
            procs[i].arrive_time = rand() % MAX_ARRIVE_TIME + 1;
            printf("Process %d arrive time: %d\n", i, procs[i].arrive_time);

            procs[i].burst_time = rand() % MAX_BURST_TIME + 1;
            printf("Process %d burst time:  %d\n", i, procs[i].burst_time);
        }
        else{
            printf("Process %d arrive time: ", i);
            scanf("%d", &procs[i].arrive_time);

            printf("Process %d burst time:  ", i);
            scanf("%d", &procs[i].burst_time);
        }
    }

    for ( int j = 0; j < n-1; ++j ){
        for ( int i = 0; i < n-1; ++i ){
            if ( procs[i].arrive_time > procs[i+1].arrive_time ){
                struct process temp = procs[i];
                procs[i] = procs[i+1];
                procs[i+1] = temp;
            }
        }
    }

    procs[0].wait_time = 0;
    procs[0].completion_time = procs[0].arrive_time + procs[0].burst_time;
    procs[0].turnaround_time = procs[0].burst_time;

    float turnaround_time_avg = procs[0].turnaround_time;
    float wait_time_avg = 0;

    for (int i = 1; i < n; ++i){
        // If there is a gap after process i finish and process i+1 arrival
        if (procs[i].arrive_time <= procs[i-1].completion_time)
            procs[i].wait_time = procs[i-1].completion_time - procs[i].arrive_time;
        else{
            procs[i].wait_time = 0;
        }
        procs[i].completion_time = procs[i].arrive_time + procs[i].burst_time + procs[i].wait_time;
        procs[i].turnaround_time = procs[i].completion_time - procs[i].arrive_time;

        turnaround_time_avg += procs[i].turnaround_time;
        wait_time_avg += procs[i].wait_time;
    }

    turnaround_time_avg /= n;
    wait_time_avg /= n;

#define COLUMN_SIZE 7
    printf("#      AT     BT     CT     TAT    WT\n");
    char str[COLUMN_SIZE*6] = "";
    char num[COLUMN_SIZE];
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < COLUMN_SIZE*6 - 1; ++j){
            str[j] = ' ';
        }
        /* printf("%d %d %d %d\n", procs[i].arrive_time, procs[i].burst_time, procs[i].completion_time, procs[i].turnaround_time); */

        sprintf(num, "%d", i);
        memcpy(str, num, strlen(num));

        sprintf(num, "%d", procs[i].arrive_time);
        memcpy(str + COLUMN_SIZE, num, strlen(num));

        sprintf(num, "%d", procs[i].burst_time);
        memcpy(str + COLUMN_SIZE*2, num, strlen(num));

        sprintf(num, "%d", procs[i].completion_time);
        memcpy(str + COLUMN_SIZE*3, num, strlen(num));

        sprintf(num, "%d", procs[i].turnaround_time);
        memcpy(str + COLUMN_SIZE*4, num, strlen(num));

        sprintf(num, "%d", procs[i].wait_time);
        memcpy(str + COLUMN_SIZE*5, num, strlen(num));

        printf("%s\n", str);
    }

    printf("Turnaround time average: %f\n", turnaround_time_avg);
    printf("Wait time average: %f\n", wait_time_avg);
}
