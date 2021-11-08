/*
 * structexample1.c
 * A simple program to introduce C structs
 *
 * Richard Lobb
 * August 2014
 */

#include <stdio.h>
#include <stdlib.h>

// Define a structure suitable for representing a student
// in a list of students. In this trivial example only
// the name and age is stored for each student.

// The following declaration declares both the structure type
// and a global instance 'student' of that type.
struct student_s {
    char* name;
    int age;
    double height;
    struct student_s* next;   // Pointer to next student in a list
};



// printOneStudent: prints a single student, passed by value
void printOneStudent(struct student_s student)
{
    printf("%s (%d), height %.2f m\n", student.name, student.age, student.height);
}

// printStudents: print all students in a list of students, passed
// by reference.
void printStudents(const struct student_s* student)
{
    while (student != NULL) {
        printOneStudent(*student);
        student = student->next;
    }
}

// main just defines fields of the two students, links them
// together into a list, and prints the list.
int main(void)
{
    // 'struct student_s' is now a type, and we can declare
    // another global variable of that type.
    struct student_s student;
    struct student_s anotherStudent;
    student.name = "Agnes McGurkinshaw";
    student.age = 97;
    student.height = 1.64;
    student.next = &anotherStudent;

    anotherStudent.name = "Jingwu Xiao";
    anotherStudent.age = 21;
    anotherStudent.height = 1.83;
    anotherStudent.next = NULL;

    printStudents(&student);
    return EXIT_SUCCESS;
}
