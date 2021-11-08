/*
 * This program contains a function that returns a pointer to an
 * n-element (dynamically-allocated) array of ints containing the values
 * from 1 to n.
 */

#include <stdio.h>
#include <stdlib.h>

//From question 3
int* ramp(int n)
{
    int* array = malloc(n * sizeof(int));
    for (int i = 1; i <= n; i++) {
        array[i - 1] = i;
    }
    return array;
}

//From question 4
void fillRamp(int* data, int n)
{
    for (int i = 1; i <= n; i++) {
        data[i - 1] = i;
    }
}

int main(void) {
    int* data = malloc(4 * sizeof(int));
    fillRamp(data, 4);
    for (int i = 0; i < 4; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }
    free(data);
}
