/* A program that uses the scanf function to read an integer from input
 * and prints 'Odd' if the integer is odd, 'Even' if the integer is even
 * and 'Zero' if the integer is zero.
 */


#include <stdio.h>

int main(void)
{
    int value = 0;

    printf("Please input an integer: "); //I omitted this in the submission
    scanf("%d", &value);
    if (value == 0) {
        printf("Zero");
    } else if ((value % 2) == 0) {
        printf("Even");
    } else {
        printf("Odd");
    }
}
