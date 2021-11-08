#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int num = -1;
    int sumEven = 0;
    int sumOdd = 0;

    while (num != 0) {
        scanf("%d", &num);
        if (num % 2 == 0) {
            sumEven += num;
        } else {
            sumOdd += num;
        }
    }

    printf("%d\n", (sumEven - sumOdd));

    return EXIT_SUCCESS;
}
