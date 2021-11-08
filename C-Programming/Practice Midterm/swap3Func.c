/* A funciton that swaps the values of the integers pointed to into
 * a specific ordering. If x points to an integer a and y points to an
 * integer b and z points to an integer c then the values should be
 * shuffled such that a <= b <= c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void swap3(int* x, int* y, int* z)
{
    int temp1;

    if (*x > *y) {
        temp1 = *x;
        *x = *y;
        *y = temp1;
    }
    if (*x > *z) {
        temp1 = *x;
        *x = *z;
        *z = temp1;
    }
    if (*y > *z) {
        temp1 = *y;
        *y = *z;
        *z = temp1;
    }
}

int main(void)
{
    int a = 10;
    int b = 0;
    int c = 7;
    swap3(&a, &b, &c);
    printf("%d <= %d <= %d\n", a, b, c);
}
