#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSES 6
#define MIN_PROCESSES 3
#define MAX_ARRIVE_TIME 5
#define MAX_BURST_TIME 5

#define DEBUG 0

struct process{
    int arrive_time;
    int start_time;
    int burst_time;
    int completion_time;
    int wait_time;
    int turnaround_time;
};

struct node{
    struct process* this;
    struct node* next;
};

// PRIORITY QUEUE ENQUEUE
void enqueue(struct node* q, struct process* proc){
    struct node* node = q;
    if (q->this == NULL){
        q->this = proc;
        return;
    }
    if ( proc->burst_time < node->this->burst_time ){
        struct node* new_node = malloc(sizeof(struct node));
        new_node->next = q->next;
        q->next = new_node;
        new_node->this = q->this;
        q->this = proc;
        return;
    }
    struct node* new_node = malloc(sizeof(struct node));
    new_node->this = proc;
    new_node->next = NULL;
    while( node->next != NULL ){
        if ( proc->burst_time < node->next->this->burst_time ){
            new_node->next = node->next;
            node->next = new_node;
            return;
        }
        node = node->next;
    }
    node->next = new_node;
}

struct process* dequeue(struct node* q){
    if ( q->this == NULL ){
        return NULL;
    }
    struct process* to_ret = q->this;
    if ( q->next ){
        struct node* to_free = q->next;
        q->this = q->next->this;
        q->next = q->next->next;
        free( to_free );
    }
    else{
        q->this = NULL;
    }
    return to_ret;
}

void print_queue(struct node* q){
    if ( q->this == NULL ){
        printf("empty\n");
        return;
    }
    printf("%d %d, ", q->this->arrive_time, q->this->burst_time);
    while (q->next != NULL){
        printf("%d %d, ", q->next->this->arrive_time, q->next->this->burst_time);
        q = q->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    time_t t;
    srand((unsigned) time(&t));
    int n = 0;
    int random = 0;
    char generate[20] = "n";
    struct process procs[MAX_PROCESSES];

    // READ INPUT
    printf("Generate input randomly? [y/n]: ");
    scanf("%s", generate);

    if ( strcmp(generate, "y") == 0 || strcmp(generate, "Y") == 0 ){
        random = 1;
        n = rand() % (MAX_PROCESSES-MIN_PROCESSES) + MIN_PROCESSES;
        printf("Number of processes: %d\n", n);
    }
    else{
        printf("Please don't enter big numbers (>2 digits), the output might break.\n");
        printf("Number of processes: ");
        scanf("%d", &n);
    }

    for (int i = 0; i < n; ++i){
        if ( random ) {
            procs[i].arrive_time = rand() % MAX_ARRIVE_TIME;
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

    // SORT BASED ON ARRIVE TIME
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

    int index = 0;
    int current_time = -1;

    struct node queue;
    queue.this = NULL;
    queue.next = NULL;

    // LOOP SIMULATING SCHEDULER
    struct process* current = NULL;
    while (1){
        if ( DEBUG ) {
            printf("current time: %d\n", current_time);
        }
        current_time++;
        for (int i = index; i < n; ++i){
            if ( procs[i].arrive_time != current_time ){
                break;
            }
            if ( DEBUG ) {
                printf("adding %d\n", index);
            }
            enqueue(&queue, &procs[i]);
            index++;
        }
        if (current != NULL){
            if ( current->burst_time + current->start_time == current_time ){
                current->completion_time = current_time;
                current->turnaround_time = current->completion_time - current->arrive_time;
                if ( DEBUG ) {
                    printf("Current: AT:%d  BT:%d  CT:%d ST:%d TAT:%d WT:%d\n", current->arrive_time, current->burst_time, current->completion_time,
                            current->start_time, current->turnaround_time, current->wait_time);
                }
                turnaround_time_avg += current->turnaround_time;
                wait_time_avg += current->wait_time;
                current = NULL;
            }
        }
        if (current == NULL) {
            if (queue.this != NULL){
                current = dequeue(&queue);
                current->wait_time = current_time - current->arrive_time;
                current->start_time = current_time;
            }
        }

        if ( (index >= n && queue.this == NULL && current == NULL) || current_time > 1000 ){
            break;
        }
    }


    turnaround_time_avg /= n;
    wait_time_avg /= n;

    // PRINT RESULTS
#define COLUMN_SIZE 7
    printf("# AT     BT     CT     TAT    WT     ST\n");
    char str[COLUMN_SIZE*7] = "";
    char num[COLUMN_SIZE];
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < COLUMN_SIZE*7 - 1; ++j){
            str[j] = ' ';
        }

        sprintf(num, "%d", i);
        memcpy(str, num, strlen(num));

        sprintf(num, "%d", procs[i].arrive_time);
        memcpy(str + 2, num, strlen(num));

        sprintf(num, "%d", procs[i].burst_time);
        memcpy(str + 2 + COLUMN_SIZE, num, strlen(num));

        sprintf(num, "%d", procs[i].completion_time);
        memcpy(str + 2 + COLUMN_SIZE*2, num, strlen(num));

        sprintf(num, "%d", procs[i].turnaround_time);
        memcpy(str + 2 + COLUMN_SIZE*3, num, strlen(num));

        sprintf(num, "%d", procs[i].wait_time);
        memcpy(str + 2 + COLUMN_SIZE*4, num, strlen(num));

        sprintf(num, "%d", procs[i].start_time);
        memcpy(str + 2 + COLUMN_SIZE*5, num, strlen(num));

        printf("%s\n", str);
    }

    printf("Turnaround time average: %f\n", turnaround_time_avg);
    printf("Wait time average: %f\n", wait_time_avg);
}
