#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char returned[1024*1024];
    printf("Welcome to the t-shell!\n");
    const char* EXITSTR = "exit";
    while (1) {
        char command[1024];
        printf("$ ");
        scanf(" %[^\n]", command);
        while (strcmp(command, EXITSTR) == 0){
            exit(0);
            return 0;
        }
        system(command);
    }
}
