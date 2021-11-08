/* structExample4.c
 * structExample3.c rewritten to use dynamically allocated memory
 * for the students and also for their names.
 *
 * WARNING: this program has a deliberate bug that causes a memory
 * leak.
 *
 * Author: Richard Lobb
 * Date: 13 August 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 80      // The longest line this program will accept

/* Note that the definitions for the maximum number of students and
 * the maximum length of a student's name are no longer required.
 */

/* The declaration of the student record (or struct). Note that
 * the struct now contains a pointer to a dynamically allocated
 * name rather than reserving a fixed amount of space within the
 * struct for the name.
 */
typedef struct student_s Student;

struct student_s {
    char* name;
    int age;
    Student* next;      // Pointer to next student in a list
};

// *** The pool of students has been deleted from here. ***

/*
 * Return a pointer to a new dynamically allocated student struct
 * that contains a pointer to a dynamically-allocated name string.
 * Returns NULL if either malloc fails.
 * Note the need to allocate one byte more than the length of the
 * string when allocating space for a copy of it, in order to make
 * space for the null terminator.
 */
Student* newStudent(const char* name, int age)
{
    size_t nameLength = strlen(name);
    Student* student = malloc(sizeof(Student));
    if (student != NULL) {
        if ((student->name = malloc(nameLength + 1)) != NULL) {
            strncpy(student->name, name, nameLength + 1);
            student->age = age;
            student->next = NULL;
        } else {  // No space for name
            free(student);
            student = NULL;
        }
    }
    return student;
}


// Free the memory allocated for a student and their name
void freeStudent(Student* student)
{
    free(student->name); // Must do this first (why?)
    free(student);
}


/* Read a single student from a csv input file with student name in first column,
 * and student age in second.
 * Returns: A pointer to a Student record, or NULL if EOF or an invalid
 * student record is read. Blank lines, or lines in which the name is
 * longer than the provided name buffer, or there is no comma in the line
 * are considered invalid.
 */
Student* readOneStudent(FILE* infile)
{
    char buffer[MAX_LINE_LENGTH];  // Buffer into which we read a line from stdin
    Student* student = NULL;           // Pointer to a dynamically allocated student record

    // Read a line, extract name and age

    char* line = fgets(buffer, MAX_LINE_LENGTH, infile);
    if (line != NULL) {           // Proceed only if we read something
        char* commaPos = strchr(buffer, ',');
        if (commaPos != NULL) {
            int age = atoi(commaPos + 1);
            *commaPos = '\0';  // null-terminate the name
            student = newStudent(buffer, age);
        }
    }
    return student;
}

/* Reads a list of students from a given file. Input stops when
 * a blank line is read, or an EOF occurs, or an illegal input
 * line is encountered.
 * Returns: a pointer to the first student in the list or NULL if no
 * valid student records could be read.
 */
Student* readStudents(FILE* infile)
{
    Student* first = NULL;      // Pointer to the first student in the list
    Student* last = NULL;       // Pointer to the last student in the list
    Student* student = readOneStudent(infile);
    while (student != NULL) {
        if (first == NULL) {
            first = last = student;    // Empty list case
        }
        else {
            last->next = student;
            last = student;
        }
        student = readOneStudent(infile);
    }
    return first;
}


// Free all the memory allocated to a list of students.
void freeAllStudents(Student* student)
{
    Student* next = NULL;
    while (student != NULL) {
        next = student->next;
        free(student);
        student = next;
    }
}

// printOneStudent: prints a single student, passed by value
void printOneStudent(Student stud)
{
    printf("%s (%d)\n", stud.name, stud.age);
}


/* printStudents: print all students in a list of students, passed
 * by reference */
void printStudents(const Student* studPtr)
{
    while (studPtr != NULL) {
        printOneStudent(*studPtr);
        studPtr = studPtr->next;
    }
}


int main(void)
{
    FILE* inputFile = fopen("studlist.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "File not found\n");
    }
    else {
        Student* studentList = readStudents(inputFile);
        fclose(inputFile);
        printStudents(studentList);
        freeAllStudents(studentList);
    }
}
