/* A simple demonstration of the use of malloc and free to
 * construct an array of random integers of some given size.
 * Written for Lab 6, Dynamic Memory, by RJL, June 2013.
 */

#include <stdio.h>
#include <stdlib.h>

/* Return a pointer to a dynamically allocated array of doubles of
 * the given size n, filled with random values in [0,1) i.e. the range
 * of numbers greater than or equal to 0 and less than 1.
 */
double* randomArray(int n)
{
    double* numbers = malloc(n);// * sizeof(double));
    for (int i = 0; i < n; i++) {      // Fill with random numbers
        numbers[i] = (1.0 * rand()) / RAND_MAX;
        // Note numerator is converted to a double
        // to ensure floating point division is done.
    }
    return numbers;
}

int main(void)
{
    int n = 0;
    double* randomNums = NULL;
    printf("How many random doubles? ");
    scanf("%d", &n);
    randomNums = randomArray(n);
    for (int i = 0; i < n; i++) {
        printf("%.6f\n", randomNums[i]);
    }
    printf("\n");
    free(randomNums);
    return 0;
}
