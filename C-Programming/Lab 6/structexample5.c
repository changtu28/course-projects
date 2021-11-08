/* structexample5.c
 * This is structexample4.c further modified to eliminate the need for an
 * arbitrary upper limit on the length of an input line.
 *
 * WARNING: this program has a deliberate bug that causes a memory
 * leak.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_INCREMENT 10  // An artificially small value for demo purposes

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


/* Free the memory allocated for a student and their name */
void freeStudent(Student* student)
{
    free(student->name); /* Must do this first (why?) */
    free(student);
}


/* Read a single student from a csv input file with student name in first column,
 * and student age in second.
 * Returns: A pointer to a Student record, or NULL if EOF or an invalid
 * student record is read. Blank lines, or lines in which the name is
 * longer than the provided name buffer, or there is no comma in the line
 * are considered invalid.
 *
 * NOT CURRENTLY FREEING BUFF
 */
Student* readOneStudent(FILE* infile)
{
    char* buff = NULL;     // Pointer to a dynamically allocated line buffer
    Student* student = NULL;   // Pointer to a dynamically allocated student record
    int buffSize = 0;      // Number of bytes allocated to line buffer
    int i = 0;             // Line buffer index

    // Read a line, increasing buffer size as required to handle the line

    int c = '\0';   // Input characters go here
    while ((c = fgetc(infile)) != EOF && c != '\n') {
        if (i >= buffSize - 1) {             // Out of space?
            buffSize += BUFFER_INCREMENT;    // Yes. Make buffer bigger
            buff = realloc(buff, buffSize);  // Grow the space (copies if necessary)
            if (buff == NULL) {
                fprintf(stderr, "Out of memory");
                exit(EXIT_FAILURE);
            }
        }
        buff[i] = c;
        i += 1;
    }

    // Unless buff is NULL, we now have an input line. Extract name and age

    if (buff != NULL) {
        buff[i++] = '\0'; // Terminate the string
        char* commaPos = strchr(buff, ',');
        if (commaPos != NULL && commaPos > buff) {
            int age = atoi(commaPos + 1);
            *commaPos = '\0';  // null-terminate the name
            student = newStudent(buff, age);
        }
    }
    //should add free(buff); here
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
            first = last = student;  // Empty list case
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
        freeStudent(student);
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
    Student* studentList = readStudents(inputFile);
    fclose(inputFile);
    printStudents(studentList);
    freeAllStudents(studentList);
    return EXIT_SUCCESS;
}
