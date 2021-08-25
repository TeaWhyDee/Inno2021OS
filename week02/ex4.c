#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int strtoint(char *str){
    errno = 0;
    char *p;
    long n = strtol(str, &p, 10);

    if (errno != 0 || *p != '\0' || n > INT_MAX || n < INT_MIN) {
        printf("Error encountered, are you sure you entered a valid number?");
        exit(1);
    } else {
        return n;
    }
}

void swapints(int *first, int *second){
    int temp = *first;
    *first = *second;
    *second = temp;
}

int main(int argc, char *argv[]){
    char firststr[1024];
    char secondstr[1024];
    printf("Please provide an integer: ");
    scanf("%s", firststr);
    printf("Please provide another integer: ");
    scanf("%s", secondstr);

    int first = strtoint(firststr);
    int second = strtoint(secondstr);

    swapints(&first, &second);
    printf("Your ints swapped: ");
    printf("%d %d\n", first, second);
}
