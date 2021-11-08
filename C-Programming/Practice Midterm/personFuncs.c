/* Two functions: newPerson which returns a pointer to a newly allocated
 * Person with name, age and height set appropriately. The name field
 * must be dynamically allocated. The freePerson function frees all
 * memory that was allocated by newPerson when creating the Person
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* name;
    int age;
    double height;
} Person;

Person* newPerson(char* name, int age, double height)
{
    Person* person = malloc(sizeof(Person));
    size_t nameLen = strlen(name);
    person->name = malloc(nameLen + 1); //+1 for null byte
    strncpy(person->name, name, strlen(name));
    person->age = age;
    person->height = height;

    return person;
}

void freePerson(Person* person)
{
    free(person->name);
    //free(person->age);
    //free(person->height);
    free(person);
}

int main(void)
{
    Person* employee = newPerson("Billy", 30, 1.68);
    printf("%s is age %d and is %.2f m tall\n", employee->name, employee->age, employee->height);
    freePerson(employee);
}
