/* retroAlpha.c
 * A text-based adventure game (aka interactive fiction). The world is
 * represented by nodes, with a unique ID, a name and four possible
 * neighbours ([N]orth, [S]outh, [W]est, [E]ast). The specification of
 * the world is described in the world.txt file, which is read by the
 * program and converted into nodes. Five keyboard commands will be
 * accepted from the user: N, S, W, E, Q. With Q being the quit command
 * and the others representing cardinal directions.
 *
 * Author: Chang Tu
 * Date: 22/08/2018
 * Made for ENCE260 Superquiz 2
 * University of Canterbury
 */

//Don't include in answer (given to me):
#define MAX_NAME_LENGTH 20
typedef struct node_s {
    int id;
    char name[MAX_NAME_LENGTH + 1];
    int paths[4];
} Node;

//Do include in answer (my code):
//Question 2 (create the world):
#define MAX_LINE_LENGTH 100 //ie. the buffer
#define MAX_NUM_NODES 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* Reads one line from input and creates a node out of it, then returns
 * a pointer to that node */
Node readNode(FILE* file)
{
    char buffer[MAX_LINE_LENGTH];
    Node node;
    int id_num = -1;
    int nameLength = 0;

    char* line = fgets(buffer, MAX_LINE_LENGTH, file); //Read one line
    if (line != NULL && *line != '\n') { //Check if there was something in the line
        char* currentComma = strchr(buffer, ',');
        char* nextComma = NULL;
        if (currentComma != NULL) {
            nextComma = strchr((currentComma + 1), ',');
        }
        if (nextComma != NULL) {
            id_num = atoi(buffer);
            nameLength = (nextComma - (currentComma + 1));
            strncpy(node.name, (currentComma + 1), nameLength);
            node.name[nameLength] = '\0';
            node.paths[0] = atoi(nextComma + 1);
            nextComma = strchr((nextComma + 1), ',');
            node.paths[1] = atoi(nextComma + 1);
            nextComma = strchr((nextComma + 1), ',');
            node.paths[2] = atoi(nextComma + 1);
            nextComma = strchr((nextComma + 1), ',');
            node.paths[3] = atoi(nextComma + 1);
        }
    }
    node.id = id_num;
    return node;
}

//Returns number of nodes
//Fills the node list with the number of nodes
void readNodes(Node* nodeList, FILE* file)
{
    int nodeNum = 0;
    Node currentNode = readNode(file);
    //printf("%s\n", currentNode.name);
    while (currentNode.id >= 0 && nodeNum < MAX_NUM_NODES) {
        nodeList[nodeNum] = currentNode;
        currentNode = readNode(file);
        nodeNum++;
        //printf("%s\n", currentNode.name);
    }
    //return nodeNum;
}

//Returns 1 if the program ended due to a quit call (Q) or an EOF.
//Returns 0 otherwise
int runGame(Node* nodeList)
{
    char buffer[MAX_LINE_LENGTH];
    Node playerLoc = nodeList[0];
    char* directionText[] = {"East", "North", "West", "South"};
    char* line = NULL;
    char playerChoice = 0;
    int directionToGo = -1;
    //Prints the name of the beginning node to start the game
    printf("%s\n", playerLoc.name);
    while ((playerChoice != EOF) && (toupper(playerChoice) != 'Q')) {
        line = fgets(buffer, MAX_LINE_LENGTH, stdin); //Read a single line
        if (line != NULL && ((strlen(line) - 1) == 1)) {
            playerChoice = toupper(line[0]);
            if (playerChoice == 'E') {
                directionToGo = 0;
            } else if (playerChoice == 'N') {
                directionToGo = 1;
            } else if (playerChoice == 'W') {
                directionToGo = 2;
            } else if (playerChoice == 'S') {
                directionToGo = 3;
            } else {
                directionToGo = -1;
            }
        }
        if (directionToGo >= 0) {
            if (playerLoc.paths[directionToGo] < 0) {
                printf("You can't go %s\n", directionText[directionToGo]);
            } else {
                for (int index = 0; nodeList[index].id >= 0; index++) {
                    if (playerLoc.paths[directionToGo] == nodeList[index].id) {
                        playerLoc = nodeList[index];
                        break;
                    }
                }
                printf("%s to %s\n", directionText[directionToGo], playerLoc.name);
            }
        }
        directionToGo = -1;
    }
    return 1;
}


int main(int argc, char* argv[])
{
    //Check number of arguments is corerct
    if (argc != 2) {
        printf("Usage: %s worldfilename\n", argv[0]);
        exit(0);
    }

    //Check if the given filename is valid
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File '%s' can not be opened.\n", argv[1]);
        exit(0);
    }

    //Generate the array of nodes
    Node nodeList[MAX_NUM_NODES];
    readNodes(nodeList, file);

    if (runGame(nodeList) == 1) {
        printf("Bye!\n");
        exit(0);
    } else {
        printf("Bad exit -- this shouldn't happen");
        exit(1);
    }
}
