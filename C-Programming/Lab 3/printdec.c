/* A looping program that reads characters from standard input and
 * writes their decimal values to standard output one per line, until
 * EOF occurs.
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int c = 0;
    int ordinalValue = 0;

    //printf("Enter some input and I will output their decimal values!\n");

    //c = getchar();
    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            printf("'%c': Digit %c\n", c, c);
            //printf("Found digit\n");
        } else if (isalpha(c)) {
            if (c >= 'a' && c <= 'z') {
                ordinalValue = c - 'a' + 1;
            } else if (c >= 'A' && c <= 'Z') {
                ordinalValue = c - 'A' + 1;
            }
            printf("'%c': Letter %d\n", c, ordinalValue);
        } else if (c == 10) {
            printf("'\\n'\n");
        } else {
            printf("'%c': Non-alphanumeric\n", c);
        }
    }

}
