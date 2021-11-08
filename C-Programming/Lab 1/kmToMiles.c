
#include <stdio.h>

#include <stdlib.h>

#define SCALE_FACTOR 1.609344

int main(void)
{
    float kilometers;
    float miles;
    printf("How many miles? ");

    scanf("%f", &miles);
    kilometers = miles * SCALE_FACTOR;

    printf("That's %.2f km.\n", kilometers);
    return EXIT_SUCCESS;
}
