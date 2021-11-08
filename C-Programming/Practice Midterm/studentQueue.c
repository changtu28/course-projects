#include <stdio.h>

typedef struct queueElement QueueElement;

struct queueElement {
    char* username;
    QueueElement* next;
};

QueueElement* appendToQueue(QueueElement* queue, QueueElement* toAppend)
{
    if (queue == NULL) {
        return toAppend;
    } else {
        QueueElement* current = queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = toAppend;
        return queue;
    }


}

// Print the elements in the given queue of users preceded by the word
// 'Queue' and the supplied message.
void printQueue(QueueElement* queue, const char* message)
{
    QueueElement* current = queue;
    printf("Queue %s:", message);

    while (current != NULL) {
        printf(" %s", current->username);
        current = current->next;
    }
    printf("\n");
}


// Simple test of the student queue
int main(void)
{
    QueueElement* queue = NULL;
    QueueElement stud1 = {"abc24", NULL};
    QueueElement stud2 = {"pqr33", NULL};

    printQueue(queue, "at start");
    queue = appendToQueue(queue, &stud1);
    printQueue(queue, "after appending abc24");
    queue = appendToQueue(queue, &stud2);
    printQueue(queue, "after appending pqr33");
}
