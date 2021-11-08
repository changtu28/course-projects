/* A program that reads a single integer from standard input and then
 * prints (to standard output) the squares of the integers from 1 up to
 * that integer, one per line
 */

#include <stdio.h>

int main(void)
{
    int n = 0;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", (i * i));
    }
}
