

#include <stdio.h>
#include <stdbool.h>

char data[100];

bool isInData(char* p)
/* A function that returns 1 (true) if and only if p points somewhere
 * within the array 'data'
 */
{
    return (p >= data && p < (data + 100));
}

bool isInData2(char data[], int arraySize, char* ptr)
/* A function that returns 1 (true) if and only if ptr points somewhere
 * within the array 'data'
 */
{
    return (ptr >= data && ptr < (data + arraySize));
}

int main(void)
{
    printf("Tests for isInData:\n");
    printf("%d\n", isInData(&data[0]));
    printf("%d\n", isInData(&data[17]));
    printf("%d\n", isInData(&data[99]));
    printf("%d\n", isInData(&data[100]));


    printf("\n\nTests for isInData2:\n");
    char x;
    char thing[3];
    char y;
    printf("%d\n", isInData2(thing, 3, &x));
    printf("%d\n", isInData2(thing, 3, &thing[0]));
    printf("%d\n", isInData2(thing, 3, &thing[1]));
    printf("%d\n", isInData2(thing, 3, &thing[2]));
    printf("%d\n", isInData2(thing, 3, &thing[3]));
    printf("%d\n", isInData2(thing, 3, &y));

    printf("\nMy tests for isInData2:\n");
    printf("%d\n", isInData2(data, 100, &data[0]));
    printf("%d\n", isInData2(data, 100, &data[17]));
    printf("%d\n", isInData2(data, 100, &data[99]));
    printf("%d\n", isInData2(data, 100, &data[100]));
}
