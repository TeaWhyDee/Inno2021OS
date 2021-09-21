#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>

void * myThread(void* arg){
    printf("  Thread %d running...\n", ((int)(intptr_t) arg));
    pthread_exit( NULL );
}

int main(int argc, char *argv[]){
    int n = 50;
    pthread_t threads[n];
    int args[50];
    for (int i = 0; i < n; ++i){
        args[i] = i+1;
        if (pthread_create(&threads[i], NULL, &myThread, (void*)(intptr_t)(i+1))) {
            printf("ERROR");
            return 1;
        }
        else {
            printf("Creating thread %d\n", i+1);
        }
        pthread_join(threads[i], NULL);
        printf("Thread joined \n");
    }
}
