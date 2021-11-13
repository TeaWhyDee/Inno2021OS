#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[]){
    char filename[16] = "input.txt";
    char o_filename[16] = "output.txt";
    FILE *input_f;
    FILE *output_f;
    input_f = fopen(filename, "r");
    output_f = fopen(filename, "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int amount_types = 0;
    int amount_processes = 0;
    int E[128] = {0};
    int A[128] = {0};
    int C[128][128];
    int R[128][128];
    memset(C, 0, sizeof C);
    memset(R, 0, sizeof R);

    // E
    if ((read = getline(&line, &len, input_f)) != -1){
        char* p = line;
        while (*p) {
            if ( isdigit(*p) ) {
                E[amount_types] = strtol(p, &p, 10);
                amount_types++;
            } else { p++; }
        }
    } else { exit (-1); }
    getline(&line, &len, input_f);

    {  // A
        read = getline(&line, &len, input_f);
        char* p = line;
        for (int i = 0; i < amount_types; ++i){
            while (!isdigit(*p)){
                p++;
            }
            A[amount_types] = strtol(p, &p, 10);
        }
    }
    getline(&line, &len, input_f);

    do { // C
        getline(&line, &len, input_f);
        char* p = line;
        for (int i = 0; i < amount_types; ++i){
            while (!isdigit(*p)){
                p++;
            }
            C[amount_processes][i] = strtol(p, &p, 10);
        }
        amount_processes++;
    } while ( strlen(line) > 2 );
    amount_processes--;

    // R
    for (int j = 0; j < amount_processes; ++j){
        getline(&line, &len, input_f);
        char* p = line;
        for (int i = 0; i < amount_types; ++i){
            while (!isdigit(*p)){
                p++;
            }
            R[j][i] = strtol(p, &p, 10);
        }
    }

    for (int i = 0; i < amount_types; ++i){
        printf("%d ", E[i]);
    } printf("\n\n");

    for (int i = 0; i < amount_types; ++i){
        printf("%d ", A[i]);
    } printf("\n\n");

    for (int j = 0; j < amount_processes; ++j){
        for (int i = 0; i < amount_types; ++i){
            printf("%d ", C[j][i]);
        }
        printf("\n");
    } printf("\n\n");

    for (int j = 0; j < amount_processes; ++j){
        for (int i = 0; i < amount_types; ++i){
            printf("%d ", R[j][i]);
        }
        printf("\n");
    } printf("\n\n");

    int amount_deadlocked = amount_processes;
    int marked[128] = {0};
    for (int i = 0; i < amount_processes; ++i){
        int good = 0;
        printf("i: %d\n", i);
        for (int j = 0; j < amount_processes; ++j){
            if ( marked[j] == 0 ){
                good = 1;
                for (int k = 0; k < amount_types; ++k){
                    if (R[j][k] > A[k]){
                        good = 0;
                    }
                }
                if (good == 1) {
                    marked[j] = 1;
                    amount_deadlocked--;
                    for (int k = 0; k < amount_types; ++k){
                        A[k] += C[j][k];
                    }
                    break;
                }
            }
        }
    }

    if (amount_deadlocked > 0){
        printf("%d", amount_deadlocked);
    }
    else {
        printf("No deadlocked processes");
    }

    return 0;
}
