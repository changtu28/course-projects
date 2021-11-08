/* My first minless C program :) */

#include <stdio.h>

int main(void)
{
    //Declarations
    int number1;
    int number2;
    int total;
    int n = 60000;

    //Code
    number1 = 10;
    number2 = 20;
    total = number1 + number2;
    printf("The sum of %d and %d is %d\n", number1, number2, total);
    printf("Big number = %d\n", n * 60000);

    return 0;
}
