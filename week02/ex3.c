#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


int main(int argc, char *argv[]){
    if (argc <= 1){
        printf("Please provide an integer number as argument");
        exit(1);
    }
    errno = 0;
    char *p;
    long n = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || n > INT_MAX || n < INT_MIN) {
        printf("Error encountered, are you sure you entered a valid number?");
        return 1;
    } else {
        printf("%ld\n", n);
    }

    for (int i = 1; i < n+1; ++i){
        for (int j = 0; j < (n-i); ++j){
            putchar(' ');
        }
        for (int j = 0; j < i*2-1; ++j){
            putchar('*');
        }
        putchar('\n');
    }
}
