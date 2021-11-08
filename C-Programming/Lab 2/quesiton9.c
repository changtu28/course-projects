/* A program that uses a do-while loops to read integers from standard
 * input and prints each one on a line by itself until the number 42 has
 * been printed.
 */

#include <stdio.h>

int main(void)
{
    int value = 0;

    do {
        scanf("%d", &value);
        printf("%d\n", value);
    } while (value != 42);
}
