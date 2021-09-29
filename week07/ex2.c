#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    int N;
    printf("Please input the size of array: ");
    scanf("%d", &N);

    int *array = malloc( sizeof(int) * N );
    for (int i = 0; i < N; ++i){
        array[i] = i;
        printf("%d", array[i]);
        if ( i < N-1 ){
            printf(", ");
        }
    }

    free(array);
}
