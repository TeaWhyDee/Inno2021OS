#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/**
  A fatal race condition accurs on average after a few hundred thousand iterations.
  */

int buffer[10];
int count = 0;
int iterations = 0;

int consumer_sleeping = 0;
int producer_sleeping = 0;

void* consumer(void *args) {
    while(1) {
        iterations++;
        if (consumer_sleeping == 1){
            continue;
        }
        if (count == 0){
            producer_sleeping = 0;
            consumer_sleeping = 1;
            continue;
        }
        else{
            int n = buffer[count-1];
            count--;
        }
    }
}

void* producer(void *args) {
    while(1) {
        iterations++;
        if (producer_sleeping == 1){
            continue;
        }
        if (count >= 10){
            consumer_sleeping = 0;
            producer_sleeping = 1;
            continue;
        }
        else {
            int n = rand() % 1000;
            buffer[count] = n;
            count++;
        }
    }
}

void *print(void *args) {
    while(1) {
        printf("count: %d , iterations: %d\n", count, iterations);
        sleep(0.10);
    }
}

#define AMOUNT_CONSUMERS 1
#define AMOUNT_PRODUCERS 1

int main(int argc, char *argv[]){
    pthread_t threads[AMOUNT_CONSUMERS+AMOUNT_PRODUCERS];
    for (int i = 0; i < AMOUNT_CONSUMERS; ++i){
        if (pthread_create(&threads[i], NULL, &consumer, NULL)) {
            printf("ERROR creating thread");
            return 1;
        }
    }
    for (int i = AMOUNT_CONSUMERS; i < AMOUNT_PRODUCERS+AMOUNT_CONSUMERS; ++i){
        if (pthread_create(&threads[i], NULL, &producer, NULL)) {
            printf("ERROR creating thread");
            return 1;
        }
    }
    if (pthread_create(&threads[AMOUNT_CONSUMERS+AMOUNT_PRODUCERS+1], NULL, &print, NULL)) {
        printf("ERROR creating thread");
        return 1;
    }
    for (int i = 0; i < 2; ++i){
        if (pthread_join(threads[i], NULL) != 0) {
            printf("ERROR joining thread");
            return 1;
        }
    }
}
