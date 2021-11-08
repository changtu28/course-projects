#include <stdio.h>

void printViaPtr(const int* intPtr)
{
    printf("%d\n", *intPtr);
}

void print2ints(int i, int j)
{
    printViaPtr(&i);
    printViaPtr(&j);
}

int main(void)
{
    print2ints(11, -93);
}
