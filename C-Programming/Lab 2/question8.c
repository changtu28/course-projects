/* A program that reads integers from standard input and prints each one
 * on a line by itself until the number 42 has been printed.
 */

#include <stdio.h>

int main(void)
{
    int value = 0;

    while (value != 42) {
        scanf("%d", &value);
        printf("%d\n", value);
    }
}
