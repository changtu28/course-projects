
#include <stdio.h>

//typedef struct pizza Pizza;

typedef struct {
    char* type;
    int energy;
    float price;
} Pizza;

int main(void)
{
    Pizza pizza = {"Hawaiian", 929, 1.0};
    printf("A slice of %s pizza costs $%.2f and contains %d kJ of energy.\n", pizza.type, pizza.price, pizza.energy);
}
