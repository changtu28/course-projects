/* Program to demonstrate various heap mismanagement problems.
 * Reads lines from a given file into an array of strings,
 * prints them all out and frees them.
 * BUGGY!
 * Written for COSC208, Richard Lobb, 2007, 2008, 2009; ENCE260 2012/3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 100

// Return a copy of the string s
char* copyString(char* s)
{
    int len = strlen(s);
    char* copy = malloc(len);
    strcpy(copy, s);
    return copy;

    //len should be + 1 in malloc for the null byte
}

/* Read lines from the file into a dynamically allocated array of strings.
 * Returns a pointer to the array of strings, which is terminated by an
 * additional NULL pointer (i.e., there are n + 1 char* values in the array,
 * with the last value being NULL).
 * Each string will usually end with a newline character.
 */
char** readFile(FILE *fp)
{
    char** stringBuffer = NULL;
    int numStrings = 0;
    char line[MAX_LINE_SIZE];
    stringBuffer[0] = NULL;
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        stringBuffer = realloc(stringBuffer, numStrings + 1);
        stringBuffer[numStrings] = copyString(line);
        numStrings += 1;
    }
    stringBuffer[numStrings] = NULL;  // Terminator
    return stringBuffer
    //Should free stringBuffer
}

// Print all the strings in the given string array (terminated by NULL)
void printStrings(char* s[])
{
    int i = 0;
    while (s[i] != NULL) {
        printf("%s", s[i]);
        i += 1;
    }
}

// Free all the strings in the given string array (terminated by NULL)
void freeAllStrings(char* s[])
{
    int i = 0;
    while (s[i] != NULL) {
        free(s[i]);
        i += 1;
    }
}


int main(int argc, char* argv[])
{
    FILE* inputFile = NULL;
    char** stringArray = NULL;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }
    inputFile = fopen(argv[1], "r"); /* Open file for reading */
    if (inputFile == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }
    stringArray = readFile(inputFile);
    printStrings(stringArray);
    freeAllStrings(stringArray);
    free(stringArray);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
