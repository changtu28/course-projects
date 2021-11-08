#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int n = 0;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("%d\n", (i * i * i));
    }

    return EXIT_SUCCESS;
}
