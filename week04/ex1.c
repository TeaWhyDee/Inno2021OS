#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    int pid = fork();
    int n = 4;
    switch (pid){
        case 0:
            for (int i = 0; i < n; ++i){
                printf("Hello world from child [%d - %d]\n", pid, i);
            }
            break;
        case -1:
            printf("error\n");
            break;
        default:
            for (int i = 0; i < n; ++i){
                printf("Hello world from parent [%d - %d]\n", pid, i);
            }
            break;
    }
    /* if (pid > 0){ */
    /*     printf("parent"); */
    /* } */
}
