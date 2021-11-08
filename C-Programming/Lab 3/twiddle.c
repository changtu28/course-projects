/* A program to demonstrate the (mis)use of external
 * variables. Reads a name (well, any string of chars,
 * really), converts it to upper case, then prints it
 * out.
 * Written for ENCE260, June 2011/2015/2018
 * Author: Richard Lobb
 */

#include <stdio.h>
#include <ctype.h>  // Various character-handling functions defined here

#define MAX_NAME_LENGTH  80
char name[MAX_NAME_LENGTH];  // declares a global (aka "external") variable

// Read a name (or any string) into the "name" array.
// Terminate it with null.
void readName(void)
{
    int c = 0;
    int i = 0;
    printf("Enter your name: ");
    while ((c = getchar()) != '\n' && c != EOF && i < MAX_NAME_LENGTH - 1) {
        name[i++] = c;
    }
    name[i++] = 0;  // Terminator
}

// Convert the global "name" string to upper case
void convertNameToUpper(void)
{
    int i = 0;
    while (name[i] != '\0') {
        name[i] = toupper(name[i]);
        i++;
    }
}

// Main program reads name, converts it to upper case and prints it
int main(void)
{
    readName();
    convertNameToUpper();
    printf("Your name in upper case: %s\n", name);
}
