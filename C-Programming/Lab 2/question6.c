/* A program that reads three floats from standard input a, b & c and
 * prints the solution to the quadratic equation ax^2 + bx + c = 0.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    float a = 0;
    float b = 0;
    float c = 0;
    float discriminant = 0;
    float root1 = 0;
    float root2 = 0;

    scanf("%f %f %f", &a, &b, &c);

    discriminant = (b * b) - (4 * a * c);

    if (a == 0) {
        printf("Not a quadratic\n");
    } else if (discriminant < 0) {
        printf("Imaginary roots\n");
    } else {
        root1 = ((-b + sqrt(discriminant)) / (2 * a));
        root2 = ((-b - sqrt(discriminant)) / (2 * a));
        if (root2 > root1) {
            printf("Roots are %.4f and %.4f", root1, root2);
        } else {
            printf("Roots are %.4f and %.4f", root2, root1);
        }
    }
}
