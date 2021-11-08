/* Program to introduce the 'char' data type, plus the use of getchar and
 * putchar to read and write chars from/to standard input.
 * Reads characters from stdin, printing each one out in both decimal and octal,
 * until '\n' or end-of-file is reached.
 * Written for ENCE260 by RJL.
 * June 2016
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char someChar = 0;          // A character
    int c = 0;                  // An int with a char in its low byte

    someChar = '*';
    printf("someChar = %c\n", someChar); // Print a single char

    printf("Enter a line of text, terminated by 'Enter'\n");

    // Read and print characters until newline or End-Of-File
    c = getchar();              // Get char (cast to int) or EOF
    while (c != '\n' && c != EOF) {
        printf("Character '%c', decimal %d, octal %o, hexadecimal %x\n", c, c, c, c);
        c = getchar();
    }

    int x = 0;
    x = '\40';
    printf("Character: >%c<", x);

    return EXIT_SUCCESS;
}
