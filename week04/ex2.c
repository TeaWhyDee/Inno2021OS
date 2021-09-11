#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    for (int i = 0; i < 3; ++i){
        int pid = fork();
        printf("%d\n", pid);
    }
    /* sleep(5); */
}
