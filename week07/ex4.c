#include <stdio.h>
#include <stdlib.h>

int* my_realloc( int* pointer, long int old_size, long int new_size ){
    printf("sizeof new array in bytes: %ld\n", new_size );
    printf("sizeof 1st element: %ld\n", sizeof(pointer[0]) );
    printf("old size: %ld\n", new_size / sizeof( pointer[0] ) );
    if ( pointer == NULL ){
        if ( new_size != 0 ) {
            int* new_pointer = malloc( new_size );
            return new_pointer;
        }
        else{
            return NULL;
        }
    }
    if ( new_size == 0 ){
        free(pointer);
        return NULL;
    }

    int* new_pointer = malloc( new_size );
    int iterations = old_size < new_size ? old_size : new_size;
    iterations /= sizeof(int);
    for (int i = 0; i < iterations; ++i){
        new_pointer[i] = pointer[i];
    }

    free(pointer);
    return new_pointer;
}

int main(int argc, char *argv[]){
    printf("Enter original array size:");
    int n1=0;
    scanf("%d",&n1);

    int* a1 = malloc( sizeof(int) * n1 );
    for(int i=0; i<n1; i++){
        a1[i]=100;
        printf("%d ", a1[i]);
    }
    printf("\nEnter new array size: ");
    int n2=0;
    scanf("%d",&n2);

    a1 = my_realloc(a1, sizeof(int) * n1, sizeof(int) * n2);

    /* if ( n2 > n1 ){ */
    /*     for (int i = n1; i < n2; ++i){ */
    /*         a1[i] = 0; */
    /*     } */
    /* } */
    for(int i=0; i<n2;i++){
        printf("%d ", a1[i]);
    }
    printf("\n");

}
