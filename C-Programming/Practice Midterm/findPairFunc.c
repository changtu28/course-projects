/* A function that searches within the first 'numE;s' of a given int
 * array ('data') for an element equal to first followed immediately
 * by an element second. If this condition is true then the function
 * returns a pointer to the lement first. If no such condition is
 * satisfied, the function returns NULL
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int* findPair(int* data, int numEls, int first, int second)
{
    for (int i = 0; i < numEls; i++) {
        if (data[i] == second && i != 0) {
            if (data[i - 1] == first) {
                return &data[i - 1];
            }
        }
    }
    return NULL;
}

int main(void)
{
    int data[] = {1, 10, 3, 20, 1, 3, 7};
    int* p = findPair(data, 7, 1, 3);
    if (p != NULL) {
        printf("Found at position %zd\n", p - data);
    }
    else {
        puts("Not found");
    }

    int data2[] = {1, 10, 2, 1, 2, 1, 2};
    int* p2 = findPair(data2, 7, 1, 2);
    if (p2 != NULL) {
        printf("Found at position %zd\n", p2 - data2);
    }
    else {
        puts("Not found");
    }
}
