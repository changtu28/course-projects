/*
 * Takes a string as input and returns a new (dynamically-allocated)
 * string containing every second charact of the input starting with
 * the first character
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* skipping(const char* s)
{
    char* skippingString = NULL;
    int i = 0;
    int mem = 1;
    while (s[i] != EOF && s[i] != '\0') {
        if (i % 2 == 0) {
            skippingString = realloc(skippingString, mem + 1); //+1 for null byte, +1 so that it allocated 1 for the first time
            skippingString[mem - 1] = s[i];
            mem++;
        }
        i++;
    }
    if (skippingString != NULL) {
        skippingString[mem - 1] = '\0';
    }
    return skippingString;
}


int main(void)
{
    char* s = skipping("");
    printf("%s\n", s);
    free(s);
}
