
// Program to demonstrate use of pointers to manipulate arrays

#include <stdio.h>

void arrayPrinter1(const int a[], int n)
// A simple Java-like version using array indexing
{
    printf("arrayPrinter1:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n\n");
}

void arrayPrinter2(const int* a, int n)
// A version using pointer arithmetic instead of indexing
{
    printf("arrayPrinter2:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(a + i));
    }
    printf("\n\n");
}

void arrayPrinter3(const int* a, int n)
// A version using autoincrement on a pointer
{
    printf("arrayPrinter3:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", *a++);
    }
    printf("\n\n");
}

void arrayPrinter4(const int* a, int n)
// A version that dispenses with a loop control variable
{
    const int* endOfArray = a + n;
    printf("arrayPrinter4:\n");
    while (a < endOfArray) {
        printf("%d ", *a++);
    }
    printf("\n\n");
}

int main(void)
{
    int data[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    arrayPrinter1(data, 10);
    arrayPrinter2(data, 10);
    arrayPrinter3(data, 10);
    arrayPrinter4(data, 10);
    return 0;
}
