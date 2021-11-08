#include <stdio.h>

int tokenCopy(char* dest, const char* src, int destSize)
{
    int charsCopied = 0;
    while (*src != '\0' && charsCopied < (destSize - 1) && *src != ' ') {
        *dest = *src;
        dest++;
        charsCopied++;
        src++;
    }
    *dest = '\0'; //Correctly terminate destination string
    return charsCopied;
}

int main(void)
{
    char buff[5];
int n = tokenCopy(buff, "This is a string", 5);
printf("%d '%s'\n", n, buff);
}
