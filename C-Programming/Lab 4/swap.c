/* A functon that swaps the values of two integers (using pointers)
 */

#include <stdio.h>

void swap(int* pi, int* pj)
{
    int temp = *pi;
    //int tempLoc = &pi;
    *pi = *pj;
    *pj = temp;
}

void oof(char* p1, char* p2)
{
    *p1 = *p2;
}

void blah()
{
    char c = 'X';
    char other = 'Y';
    oof(&other, &c);
    printf("%c\n", other);
}

int main(void)
{
    blah();
}
