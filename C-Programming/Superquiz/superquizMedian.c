/* This program takes traffic information going accross a pressure pad
 * and returns a number of statistics. The total number of vehicles
 * (including ones with trailers), the number of trailers, the minimum
 * speed in km/h of the vehicles, the maximum speed in km/h of the
 * vehicles and the average speed in km/h of the vehicles
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Question 1
int readInts(int maxNumInts, int nums[])
/* A function which reads whitespace seperated integers from standard
 * input until the maximum count is reached, EOF occurs or a non-int is
 * ecountered. It returns the number of valid values in the input
 */
{

    int intCount = 0;
    int current = 0;
    int check = 0;


    check = scanf(" %d", &current); //Space means skip whitespace
    //nums[intCount] = current;
    //intCount++;
    do {
        nums[intCount] = current;
        intCount++;
        check = scanf(" %d", &current);
    } while (intCount < maxNumInts && current != EOF && check > 0);

    return intCount;
}

int compare_floats(const void* float1, const void* float2)
{
    if (*(float*)float1 > *(float*)float2) {
        return 1;
    } else if (*(float*)float1 < *(float*)float2) {
        return -1;
    } else {
        return 0;
    }
}

float getMedian(float array[], int arraySize)
{
    float median;

    //for (int i = 0; i < arraySize; i++) {
    //    printf("%f ", array[i]);
    //}

    if (arraySize % 2 == 0) { //Number elements is even
        median = (array[arraySize / 2] + array[(arraySize / 2) - 1]) / 2; //Get middle two value and get mean
        //printf("Even");
    } else {
        //printf("Odd");
        median = array[(arraySize / 2)]; //Integer division will round
    }
    return median;
}

void processData(float stats[])
{
    int nums[10000];
    int maxVal = readInts(10000, nums);
    float speeds[maxVal];
    int i = 0;
    int speedNum = 0;

    while (i < maxVal) {
        float timeBetween_ms = nums[i+1] - nums[i];
        float timeBetween_s = timeBetween_ms / 1000;
        float speed_mps = 2.6 / timeBetween_s;
        float speed_kph = speed_mps * (10 / 2.77778);
        stats[0] += 1;              //Increase vehicle count

        if (speed_kph < stats[2]) { //Less than minimum
            stats[2] = speed_kph;
        }
        if (speed_kph > stats[3]) { //Greater than maximum
            stats[3] = speed_kph;
        }
        //avgSum += speed_kph;        //Add the speed to the total sum of speeds

        float timeBetweenTrailer_ms = nums[i+2] - nums[i+1];
        float timeBetweenTrailer_s = timeBetweenTrailer_ms / 1000;
        float distTravelledTrailer = timeBetweenTrailer_s * speed_mps;
        if (distTravelledTrailer < (2 * 2.6) && distTravelledTrailer > 0) {
            i += 1;
            stats[1] += 1; //Add a trailer
        }

        i += 2;
        speeds[speedNum] = speed_kph;
        speedNum++;
    }
    qsort(speeds, speedNum, sizeof(float), compare_floats);
    stats[4] = getMedian(speeds, (speedNum));
}

int main(void)
{
    //Custom tests
    //int test = 0;
    //int chek = 0;
    //chek = scanf("%d ", &test);
    //printf("Curren222t:%d, Check:%d\n", test, chek);

    //Question 1 tests
    int nums[5] = {-1, -1, -1, -1, -1};
    int n = readInts(4, nums);
    printf("n = %d\n", n);
    for (int i = 0; i < 5; i++) {
        printf("nums[%d] = %d\n", i, nums[i]);
    }

    /*
    float stats[] = {0, 0, INFINITY, -INFINITY, 0};
    processData(stats);
    printf("Vehicle count: %d\n", (int) stats[0]);
    printf("Trailer count: %d\n", (int) stats[1]);
    printf("Min speed: %.1f km/h\n", stats[2]);
    printf("Max speed: %.1f km/h\n", stats[3]);
    printf("Median speed: %.1f km/h\n", stats[4]);*/

}
