#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>


int main(int argc, char *argv[]){
    int size = 10 * 1024 * 1024;
    char *p;
    struct rusage *usage = malloc( sizeof(struct rusage) );
    for (int i = 0;  i < 10; ++ i){
        p = malloc( size * sizeof(char) );
        memset(p, 0, size);
        getrusage( RUSAGE_SELF, usage );
        printf("\nmaximum resildent set size: %ld\n integral shareld memory size: %ld\n integral unshareld ldata size: %ld\n integral unshareld stack size: %ld\n page reclaims (soft page faul): %ld\n page faults (harld page faults): %ld\n swaps: %ld\n", usage->ru_maxrss, usage->ru_ixrss, usage->ru_idrss, usage->ru_isrss, usage->ru_minflt, usage->ru_majflt, usage->ru_nswap
              );

        sleep(1);
    }
}

// Free space was rapidly decreasing.
// My RAM was filling up ( according to top ).
// Swap was never used ( swpd, si and so were always 0 ),
// probably because I have swap disabled (what a shocker).
// After some time the process was automatically terminated .
