/* An improved (but incomplete) version of twiddle.c that
 * doesn't use external (global) variables.
 * Written for ENCE260 June 2011/2013/2018
 * Author: Richard Lobb
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 80

// Read a name (or any string) into the parameter array.
// Terminate it with null.
void readName(int maxLen, char name[])
{
    int c = 0;
    int i = 0;
    printf("Enter your name: ");
    while ((c = getchar()) != '\n' && c != EOF && i < maxLen - 1) {
        name[i++] = c;
    }
    name[i] = '\0';  /* terminator */
}

void convertStringToUpper(char name[])
{
    int i = 0;
    while (name[i] != '\0') {
        name[i] = toupper(name[i]);
        i++;
    }
}

int main(void)
{
    char name[MAX_NAME_LENGTH];
    readName(MAX_NAME_LENGTH, name);
    convertStringToUpper(name);
    printf("Your name in upper case: %s\n", name);
}
