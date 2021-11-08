/* Two functions: vector which returns a Vector3d representing the
 * vectors (x, y, z), and vectorAdd which returns a Vector3d which is
 * the vector sum (a-> + b->)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int x;
    int y;
    int z;
} Vector3d;

Vector3d vector(int x, int y, int z)
{
    Vector3d newVector = {x, y, z};
    return newVector;
}

Vector3d vectorAdd(Vector3d a, Vector3d b)
{
    int newX, newY, newZ;
    newX = a.x + b.x;
    newY = a.y + b.y;
    newZ = a.z + b.z;

    Vector3d newVector = {newX, newY, newZ};

    return newVector;
}

int main(void)
{
    Vector3d v1 = vector(1, 4, -1);
    Vector3d v2 = vector(2, 4, -1);
    Vector3d v3 = vectorAdd(v1, v2);
    printf("(%d, %d, %d)\n", v3.x, v3.y, v3.z);
}
