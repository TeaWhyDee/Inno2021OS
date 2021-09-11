#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("Welcome to the t-shell!\n");
    while (1) {
        char command[1024];
        const char* EXITSTR = "exit";
        printf("$ ");
        scanf("%s", command);
        if (strcmp(command, EXITSTR) == 0){
            exit(0);
        }
        system(command);
    }
}
