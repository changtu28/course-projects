// A test program for the "findTwoLargest" function

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void findTwoLargest(const int data[], int n, int* largest, int* secondLargest)
/* Stores the largest and second largest elements in the array 'data'
 * (with length 'n' >= 2) in the variables given by the largest and
 * secondLargest pointers.
 */
{
    if (data[0] >= data[1]) {
        *largest = data[0];
        *secondLargest = data[1];
    } else {
        *largest = data[1];
        *secondLargest = data[0];
    }
    for (int i = 2; i < n; i++) {
        if (data[i] > *secondLargest) {
            if (data[i] > *largest) {
                *secondLargest = *largest;
                *largest = data[i];
            } else {
                *secondLargest = data[i];
            }
        }
    }
}

void printArray(const int data[], int n)
// Print the first n elements of array data in braces, comma-separated
{
    if (n <= 0) {
        printf("{}");
    }
    else {
        printf("{%d", data[0]);
        for (int i = 1; i < n; i++) {
            printf(",%d", data[i]);
        }
        printf("}");
    }
}

void test_array(const int data[], int n)
// Test the function findTwoLargest on array 'data' of length 'n.
// It is assumed that n >= 2.

{
    int largest = 0, second = 0;

    findTwoLargest(data, n, &largest, &second);
    printf("The two largest elements from ");
    printArray(data, n);
    printf(" are %d and %d\n", largest, second);
}

// Next, a set of test arrays

int array1[] = { 1, 2, 3, 4, 5, 6 };
int array2[] = { 20, 19, 18 };
int array3[] = { 4, 4, 4, 4 };
int array4[] = { 17, 14 };
int array5[] = { 4, 45, 123, 3, 345, 27, 479 };

// Lastly, the main test routine.
int main()
{
    test_array(array1, 6);
    test_array(array2, 3);
    test_array(array3, 4);
    test_array(array4, 2);
    test_array(array5, 7);

    return 0;
}
