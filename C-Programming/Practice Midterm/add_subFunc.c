/* A function that, starting with a result of 0 alternatively adds and
 * subtracts values from data[] array and returns the final sum
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int add_sub(const int data[], int n)
{
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            result += data[i];
        } else {
            result -= data[i];
        }
    }
    return result;
}

int main(void)
{
    int data[4] = {1, 2, 3, 4};
    printf("%d\n", add_sub(data, 4));
}
