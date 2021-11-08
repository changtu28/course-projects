/* This program reads from standard input until EOF and prints out a
 * table of how many times each of the 26 letters of the alphabet
 * occured. Non-alphabetic characters are ignore and it is not
 * case-sensitive
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int c = 0;
    int counts[26] = {0};
    //int index = 0;

    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            c = toupper(c);
            counts[c - 'A'] += 1;
        }
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        printf("%c: %d\n", i, counts[i - 'A']);
    }
}
