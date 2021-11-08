/* A program that uses scanf to read two integers where the first is
 * greater than 1 and the second is greater than or equal to the first.
 * It then prints all the prime numbers between the two (inclusive)
 */

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int n1 = 0;
    int n2 = 0;


    scanf("%d %d", &n1, &n2);

    for (int i = n1; i <= n2; i++) {
        bool isPrime = true;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                isPrime = false;
            }
        }
        if (isPrime) {
            printf("%d\n", i);
        }
    }
}
