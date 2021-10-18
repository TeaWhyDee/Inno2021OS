#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

struct page_frame {
    int num;
    int age;
};

int main(int argc, char *argv[]){
    // READ CMD PARAMETER
    if (argc <= 1){
        printf("Please provide an integer number as argument");
        exit(1);
    }
    errno = 0;
    char *p;
    long n_page_frames = strtol(argv[1], &p, 10);

    if (errno != 0) {
        printf("Error encountered, are you sure you entered a valid number?");
        exit(1);
    } else {
        printf("%ld\n", n_page_frames);
    }

    struct page_frame page_frames[128];
    for (int i = 0; i < n_page_frames; ++i){
        page_frames[i].age = 0;
        page_frames[i].num = 0;
    }

    int amount_hits = 0;
    int amount_misses = 0;

    // READ FROM FILE AND PROCESS
    int n;
    FILE* file;
    file = fopen("Lab 09 input.txt", "r");
    while(fscanf(file, "%d", &n) != EOF){
        int hit = 0;
        for (int i = 0; i < n_page_frames; ++i){
            page_frames[i].age >>= 1;
        }
        printf("\nPage frame: %d, ", n);

        int min_age = INT_MAX;
        int frame_to_replace_idx = 0;
        for (int i = 0; i < n_page_frames; ++i){
            if (page_frames[i].num == n){
                page_frames[i].age += 65536;
                hit = 1;
                break;
            }
            if (page_frames[i].age < min_age){
                min_age = page_frames[i].age;
                frame_to_replace_idx = i;
            }
        }

        if (hit == 1){
            printf("HIT\n");
            amount_hits ++;
        }
        else{
            printf("MISS\n");
            amount_misses ++;

            page_frames[frame_to_replace_idx].age = 65536;
            page_frames[frame_to_replace_idx].num = n;
        }

        printf("frame     age\n");
        printf("===============\n");
        for (int i = 0; i < n_page_frames; ++i){
            printf(" %d      %d\n", page_frames[i].num, page_frames[i].age);
        }
    }

    printf("\nAmount of hits: %d\n", amount_hits);
    printf("Amount of misses: %d\n", amount_misses);

    float ratio = (float)amount_hits / (float)amount_misses;
    printf("Ratio: %f\n", ratio);
}
