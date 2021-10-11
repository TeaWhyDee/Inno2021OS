#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    int size = 1000 * 1024 * 1024;
    char *p;
    while(1){
        p = malloc( size * sizeof(char) );
        memset(p, 0, size);
        sleep(1);
    }

}

// Free memory space was decreasing.
// My RAM was filling up with data ( according to top ).
// Swap was never used ( si and so were always 0 ).
// After some time the process was automatically terminated .
