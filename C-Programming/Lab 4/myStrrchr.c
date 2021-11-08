#include <stdio.h>

char* mystrrchr(char* s, int c)
{
    char* location = NULL;
    while (*s != '\0') {
        if (*s == c) {
            location = s;
        }
        s++;
    }
    return location;
}

int main(void)
{
    char* s = "ENCE260";
    char* foundAt = mystrrchr(s, 'E');
    if (foundAt == NULL) {
        puts("Not found");
    }
    else {
        printf("%zu\n", foundAt - s);
    }
}
