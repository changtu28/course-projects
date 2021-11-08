/* A function that takes a string 's' and returns a pointer to a new
 * array of strings, allocated on the heap containing (in order) all
 * the 'tokens' from 's' where a token is a continuous sequence of
 * non-space charcters. The returned array must be terminated by a NULL
 * pointer. Tokens may be seperated by multiple spaces and there may be
 * extra spaces at the start an end of the string, these should be ignored
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char** split(const char* s)
{
    int buffsize = 1;
    char* buff = malloc(buffsize);
    int charNum = 0;
    int len = strlen(s);
    bool found = false;
    int wordNum = 0;
    char** words = malloc((len + 1) * sizeof(char*));

    for (int i = 0; i <= len && len != 0; i++) {
        if (s[i] != ' ') {
            found = true;
            if (charNum >= buffsize - 1) {
                buffsize += 1;
                buff = realloc(buff, buffsize);
            }
            buff[charNum] = s[i];
            buff[charNum + 1] = '\0';
            charNum++;
        }

        if (found && (s[i] == ' ' || s[i] == '\0')) { //End of word found
            found = false;

            //Add word to the array of words
            words[wordNum] = malloc(strlen(buff) + 1);
            strcpy(words[wordNum], buff);
            wordNum++;

            //Reset numbers and buffer
            buffsize = 1;
            free(buff);
            buff = malloc(buffsize);
            charNum = 0;

        }
    }
    free(buff);             //Free the last buff memory allocation
    words[wordNum] = NULL;  //Terminate the list/array

    return words;
}

/*
char** split(const char* s)
{

    int buffsize = 1;
    char* buff = malloc(buffsize);
    int charNum = 0;
    int len = strlen(s);
    bool found = false;
    //int sizeWords = 0;
    int wordNum = 0;
    char** words = malloc((len + 1) * sizeof(char*));
    //words[0] = NULL;


    for (int i = 0; i <= len && len != 0; i++) {
        //printf("'%c', ", s[i]);
        if (s[i] != ' ') {
            found = true;
            if (charNum >= buffsize - 1) {
                buffsize += 1;
                buff = realloc(buff, buffsize);
            }
            buff[charNum] = s[i];
            buff[charNum + 1] = '\0';
            charNum++;
            //printf("%s\n", buff);
        }

        if (found && (s[i] == ' ' || s[i] == '\0')) { //End of word found
            //int lens = strlen(buff);
            //printf("Size: %d\n", lens);
            //printf("Found!\n");

            //printf("String: %s, numChars: %d, strlen: %d\n", buff, charNum, lens);
            found = false;

            //Add null byte to word
            //buffsize++;
            //buff = realloc(buff, buffsize);
            //buff[charNum + 1] = '\0';

            //sizeWords += buffsize;
            //words = realloc(words, sizeWords + 1);
            //words = realloc(words, (sizeof(words) + buffsize + sizeof(char*)));
            //words = realloc(words, (((wordNum + 1) * sizeof(char*)) + 1));
            words[wordNum] = malloc(strlen(buff) + 1);
            strcpy(words[wordNum], buff);
            wordNum++;

            //Reset numbers and buffer
            buffsize = 1;
            free(buff);
            buff = malloc(buffsize);
            charNum = 0;

        }
        //free(buff);

    }

    //words = realloc(words, ((wordNum + 1) * sizeof(char *)));
    //words[wordNum] = malloc(strlen(buff));
    //strcpy(words[wordNum], buff);

    free(buff);
    words[wordNum] = NULL;

    return words;
}*/

int main(void)
{
    char** words = split("He said 'hello' to me!");
    int i = 0;
    while (words[i] != NULL) {
        puts(words[i]);
        free(words[i]);
        i += 1;
    }
    free(words);
    //Should return:
    //He
    //said
    //'hello'
    //to
    //me!
}
