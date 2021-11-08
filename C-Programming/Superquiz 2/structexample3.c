/* structexample3.c
 * A development from structexample2, this time reading
 * in an arbitrary number of students from a file, allocating
 * student structures from an array of such structures
 * (often referred to as a "pool").

 * Students could have just been read into the array directly, but
 * then one would lose the benefits of having a linked list
 * structure that allows, for example, cheap insertion and
 * deletion of students. [Note that we don't actually use those wonderful
 * features in this program, but we might do in more advanced
 * applications.]

 * The input file is assumed to be a simple .csv (comma-separated-values)
 * file, with the student in the first column and the age in the second.
 *
 * This is not a very pretty program (string processing in C is never very
 * pretty), but it is instructive :-)
 *
 * Richard Lobb, June 2013.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 80      // The longest line this program will accept
#define MAX_NUM_STUDENTS 500    // The maximum number of students this program can handle
#define MAX_NAME_SIZE 50        // The maximum allowable name length

// The declaration of the student record (or struct). Note that
// the struct contains the name as an array of characters, rather than
// containing just a pointer to the name as before.

typedef struct student_s Student;

struct student_s {
    char name[MAX_NAME_SIZE];
    int age;
    Student* next;              // Pointer to next student in a list
};


//Retruns true if and only if student1 should precede student2 in the list
bool precedes(const Student* student1, const Student* student2)
{
    int nameResult = strcmp(student1->name, student2->name);
    if (nameResult == 0) {
        return (student1->age < student2->age);
    } else {
        return (nameResult < 0);
    }
}

//Inserts the given student into the list of students in the correct
//place alphabetically. list is the first student in the list of students
//It returns the new list head (either student or list)
Student* insert(Student* student, Student* list)
{
    Student* head = list;
    Student* current = list->next;
    Student* previous = list;

    if (precedes(student, list)) {
        student->next = list;
        head = student;
        return head;
    }

    while (current != NULL && previous->next != student) {
        if (precedes(student, current)) {
            previous->next = student;
            student->next = current;
        } else {
            previous = current;
            current = current->next;
        }
    }
    if (current == NULL) {
        previous->next = student;
    }
    return head;
}

// Create a pool of student records to be allocated on demand

Student studentPool[MAX_NUM_STUDENTS];  // The student pool
int firstFree = 0;

// Return a pointer to a new student record from the pool, after
// filling in the provided name and age fields. Returns NULL if
// the student pool is exhausted.
Student* newStudent(const char* name, int age)
{
    Student* student = NULL;
    if (firstFree < MAX_NUM_STUDENTS) {
        student = &studentPool[firstFree];
        firstFree += 1;
        strncpy(student->name, name, MAX_NAME_SIZE);
        student->name[MAX_NAME_SIZE - 1] = '\0';  // Make sure it's terminated
        student->age = age;
        student->next = NULL;
    }
    return student;
}

// Read a single student from a csv input file with student name in first column,
// and student age in second.
// Returns: A pointer to a Student record, or NULL if EOF or an invalid
// student record is read. Blank lines, or lines in which the name is
// longer than the provided name buffer, or there is no comma in the line
// are considered invalid.
Student* readOneStudent(FILE* file)
{
    char buffer[MAX_LINE_LENGTH];  // Buffer into which we read a line from stdin
    Student* student = NULL;       // Pointer to a student record from the pool

    // Read a line, extract name and age

    char* inputLine = fgets(buffer, MAX_LINE_LENGTH, file);
    if (inputLine != NULL) {        // Proceed only if we read something
        char* commaPos = strchr(buffer, ',');
        if (commaPos != NULL && commaPos > buffer) {
            int age = atoi(commaPos + 1);
            *commaPos = '\0';  // null-terminate the name
            student = newStudent(buffer, age);
        }
    }
    return student;
}

// Reads a list of students from a given file. Input stops when
// a blank line is read, or an EOF occurs, or an illegal input
// line is encountered.
// Returns a pointer to the first student in the list or NULL if no
// valid student records could be read.
Student* readStudents(FILE *file)
{
    Student* first = NULL;     // Pointer to the first student in the list
    //Student* last = NULL;      // Pointer to the last student in the list
    Student* student = readOneStudent(file);
    while (student != NULL) {
        if (first == NULL) {
            first = student;   // Empty list case
        } else {
            first = insert(student, first);
            //last->next = student;
            //last = student;
        }
        student = readOneStudent(file);
    }
    return first;
}

// printOneStudent: prints a single student, passed by value
void printOneStudent(Student student)
{
    printf("%s (%d)\n", student.name, student.age);
}


// printStudents: print all students in a list of students, passed
// by reference
void printStudents(const Student* student)
{
    while (student != NULL) {
        printOneStudent(*student);
        student = student->next;
    }
}





// Main program. Read a linked list of students from a csv file, then display
// the contents of that list.
int main(void)
{

    FILE* inputFile = stdin;
    if (inputFile == NULL) {
        fprintf(stderr, "File not found\n");
    } else {
        Student* studentList = readStudents(inputFile);
        printStudents(studentList);

        // The program could now do various things that make use of
        // the linked list, like deleting students and adding new ones,
        // but the program is already quite long enough!
    }
}
