/* A program that calculates how many 'rushes' it will take to climb
 * a mountain of a given height after sliding down a certain amount
 * after each rush
 */

#include <stdio.h>

int main(void)
{
    float screeHeight = 0;
    float rushHeight = 0;
    float slideBack = 0;
    float currHeight = 0;
    int numRushes = 0;

    scanf("%f %f %f", &screeHeight, &rushHeight, &slideBack);

    if (screeHeight >= rushHeight) {
        currHeight = rushHeight;
        numRushes++;
        while (currHeight < screeHeight) {
            currHeight -= slideBack;
            currHeight += rushHeight;
            numRushes++;
        }
    }

    printf("%d\n", numRushes);
}
    /*
    for (; currHeight < screeHeight; currHeight += rushHeight) {
        currHeight -= slideBack;
        numRushes++;
    }
    */
