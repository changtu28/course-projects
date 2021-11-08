/* This program is for the countMatches function that returns a count
 * of the number of times 'searchValue' is found in the 'n'-element
 * array 'data'
 */

#include <stdio.h>

int countMatches(int n, int data[], int searchValue)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] == searchValue) {
            count++;
        }
    }
    return count;
}

int main(void)
{
    int nums[] = {1, 2, 3, 4, 1, 1, 5};
    printf("%d\n", countMatches(7, nums, 1));

    int nums2[] = {10, 20, 30};
    printf("%d\n", countMatches(3, nums2, 1));
}
