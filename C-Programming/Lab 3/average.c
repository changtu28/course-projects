/* Rather meaningless program demonstrating the use of functions.
 * Taken from the text by King, section 9.2, with slight modifications.
 */

#include <stdio.h>
#include <stdlib.h>

//double average(double a, double b);


int main(void)
{
    double x = 0.0, y = 0.0, z = 0.0;
    printf("Enter three numbers: ");
    scanf("%lf%lf%lf", &x, &y, &z);
    printf("Average of %g and %g: %g\n", x, y, average(x,y));
    printf("Average of %g and %g: %g\n", y, z, average(y,z));
    printf("Average of %g and %g: %g\n", x, z, average(x,z));
    return EXIT_SUCCESS;
}

double average(double a, double b)
{
    return (a + b) / 2;
}
