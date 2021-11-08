/* My own version of the strchr function which returns a pointer to the
 * first occurence of the character c in the string s or NULL if no
 * matching character exists
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* mystrchr(char* s, char c)
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            return &s[i];
        }
    }
    return NULL;
}

int main(void)
{
    char* s = "ENCE260";
    char* foundAt = mystrchr(s, '2');
    if (foundAt == NULL) {
        puts("Not found");
    } else {
        printf("%zd\n", foundAt - s);
}
}
