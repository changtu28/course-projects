/* This program takes traffic information going accross a pressure pad
 * and returns a number of statistics. The total number of vehicles
 * (including ones with trailers), the number of trailers, the minimum
 * speed in km/h of the vehicles, the maximum speed in km/h of the
 * vehicles and the average speed in km/h of the vehicles
 */

#include <stdio.h>
#include <math.h>

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
        //printf("Current:%d, Check:%d\n", current, check);
        check = scanf(" %d", &current);
        //scanf(" %d", &current);
    } while (intCount < maxNumInts && current != EOF && check > 0);

    return intCount;
}

void processData(float stats[])
{
    int nums[10000];
    int maxVal = readInts(10000, nums);


    //float stats[] = {n, 0, INFINITY, -INFINITY, 0};

    float avgSum = 0;


    int i = 0;
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
        avgSum += speed_kph;        //Add the speed to the total sum of speeds

        float timeBetweenTrailer_ms = nums[i+2] - nums[i+1];
        float timeBetweenTrailer_s = timeBetweenTrailer_ms / 1000;
        float distTravelledTrailer = timeBetweenTrailer_s * speed_mps;
        if (distTravelledTrailer < (2 * 2.6) && distTravelledTrailer > 0) {
            i += 1;
            stats[1] += 1; //Add a trailer
        }

        i += 2;
    }


    /*for (int i = 0; i <= (stats[0] * 2); i += 2) {
        float timeBetween_ms = nums[i+1] - nums[i];
        float timeBetween_s = timeBetween_ms / 1000;
        float speed_mps = 2.6 / timeBetween_s;
        float speed_kph = speed_mps * (10 / 2.77778);
        //stats[0]++;             //Add 1 to the number of cars
        printf("%d, %d, %d, %d, %f\n", i, i+1, nums[i], nums[i+1], speed_kph);
        if (speed_kph < stats[2]) { //Less than minimum
            stats[2] = speed_kph;
        }
        if (speed_kph > stats[3]) { //Greater than maximum
            stats[3] = speed_kph;
        }
        avgSum += speed_kph;        //Add the speed to the total sum of speeds
    }*/

    stats[4] = avgSum / stats[0];//Calculate the average speed

    //return stats;
}

int main(void)
{
    //Custom tests
    //int test = 0;
    //int chek = 0;
    //chek = scanf("%d ", &test);
    //printf("Curren222t:%d, Check:%d\n", test, chek);

    //Question 1 tests
    /*int nums[5] = {0, 0, 0, 0, 0};
    int n = readInts(4, nums);
    printf("n = %d\n", n);
    for (int i = 0; i < 5; i++) {
        printf("nums[%d] = %d\n", i, nums[i]);
    }*/

    float stats[] = {0, 0, INFINITY, -INFINITY, 0};
    processData(stats);
    printf("Vehicle count: %d\n", (int) stats[0]);
    printf("Trailer count: %d\n", (int) stats[1]);
    printf("Min speed: %.1f km/h\n", stats[2]);
    printf("Max speed: %.1f km/h\n", stats[3]);
    printf("Average speed: %.1f km/h\n", stats[4]);

}
