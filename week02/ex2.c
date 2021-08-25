#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char string[1024];
    printf("Please provide a string: ");
    scanf("%s", string);
    printf("Your string reversed: ");
    for ( int i = strlen(string)-1; i >= 0; i-- ){
        printf("%c", string[i]);
    }
    printf("\n");
}
