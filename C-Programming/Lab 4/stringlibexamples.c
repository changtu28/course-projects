// A few examples of what can be done with the string library.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ss = "\101\141";

// Although the library contains a function strcasecmp it's not part of the
// C99 standard, so although it can be linked in just fine we have to
// declare its type ourselves ...
int strcasecmp(const char* s1, const char* s2);

#define BUFFSIZE 100
#define TERMINATORS " ()."   /* Token terminators */

// A function for you to ponder over!

/* Note that a "definite article" is the syntactic name given to the
 * word "the" in English (distinguishing it from the "indefinite
 * articles "a" and "an").
 */
void doStuff(char* s1, char* s2)
{
    char buff[BUFFSIZE];        /* workspace */
    char token[BUFFSIZE];
    int countDefiniteArticles = 0;
    int buffIndex = 0;
    int buffLen = 0;
    int tokenLen = 0;
    int len = strlen(s1);

    printf("The length of s1 = %d\n", len);
    strncpy(buff, s1, BUFFSIZE);
    strncat(buff, s2, BUFFSIZE - len - 1);
    printf("The concatenation of s1 and s2 is: %s\n", buff);

    buffLen = strlen(buff);  /* Length of concatenated string */
    buffIndex = 0;           /* Current index into the buffer */

    printf("\n%s\n", "The words in the concatenated string are:");

    // Loop to extract all words from the concatenated string

    while (buffIndex < buffLen) {
        tokenLen = strcspn(&buff[buffIndex], TERMINATORS);
        if (tokenLen != 0) {
            strncpy(token, &buff[buffIndex], tokenLen);
            token[tokenLen] = '\0';
            printf("%s\n", token);
            if (strcasecmp(token, "the") == 0) {
                countDefiniteArticles++;
            }
        }
        buffIndex += tokenLen + 1;  /* Step over token and its terminator */
    }
    printf("\n%d definite article(s) found.\n", countDefiniteArticles);
}

int main(void)
{
    printf("Length of s = %ld\n%s\n", strlen(ss), ss);

    doStuff("The quick (brown) fox ", " jumped over the moon.");
    return EXIT_SUCCESS;
}
