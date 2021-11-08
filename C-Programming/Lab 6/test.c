#include <stdio.h>
#include <stdlib.h>


int main(void) {
    char* p = malloc(2);
    printf("%p\n", p);
    free(p);
    printf("%p\n", p);
}
