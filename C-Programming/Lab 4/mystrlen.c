
#include <stdio.h>

size_t mystrlen(const char* s)
{
    //char* current = *s;
    long length = 0;
    while (*s != '\0') {
        s++;
        length++;
    }
    return length;
}

int main(void)
{
    printf("%zd\n", mystrlen("ENCE260"));
}
