/* A function which performs a left rotation on the characters in a
 * string in place (pointer doesn't change). Each item gets moved to its
 * next lower position, with the first item being moved to the last pos
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* rotateLeft(char* s)
{
    char temp = s[0];
    int len = strlen(s);
    int i = 1;

    for (; i < len; i++) {
        s[i - 1] = s[i];
    }
    s[i - 1] = temp;

    return s;

}

int main(void)
{
    char s[] = "Hello World!";
    printf("%s\n", rotateLeft(s));
}
