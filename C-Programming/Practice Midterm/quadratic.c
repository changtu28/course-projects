#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int a = 0;
    int b = 0;
    int c = 0;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    if ((b * b) < (4 * a * c)) {
        printf("Roots are complex");
    } else {
        printf("Roots are real");
    }

    return EXIT_SUCCESS;
}
