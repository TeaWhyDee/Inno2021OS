#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* array, int size){
    for (int i = 0; i < size-1; ++i){
        for (int j = 0; j < size-1; ++j){
            if (array[j] < array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]){
    int a[5] = { 1,2,3,4,5 };
    bubble_sort(a, 5);
    for (int i = 0; i < 5; ++i){
        printf("%d ", a[i]);
    }
}
