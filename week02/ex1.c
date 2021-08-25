#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int main(){
    int intMax = INT_MAX;
    float floatMax = FLT_MAX;
    double doubleMax = DBL_MAX;
    printf("Integer max value: %d\n", intMax);
    printf("Float max value: %f\n", floatMax);
    printf("Double max value: %f\n", doubleMax);
    printf("Size of integer: %zuB\n", sizeof(intMax));
    printf("Size of float: %zuB\n", sizeof(floatMax));
    printf("Size of double: %zuB\n", sizeof(doubleMax));
}
