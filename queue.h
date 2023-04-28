
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} *front = NULL, *rear = NULL;

void enqueue(int value)
{
    struct Node *queue = (struct Node *)malloc(sizeof(struct Node));
    if (queue == NULL)
        printf("queue is full\n");
    else
    {
        queue->data = value;
        queue->next = NULL;
        if (front == NULL)
        {
            front = rear = queue;
        }
        else
        {
            rear->next = queue;
            rear = queue;
        }
    }
}

int dequeue()
{
    int value = -1;
    if (front == NULL)
        printf("queue is empty\n");
    else
    {
        struct Node *queue = front;
        front = front->next;
        value = queue->data;
        free(queue);
    }
    return value;
}

void printQ()
{
    struct Node *node = front;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
