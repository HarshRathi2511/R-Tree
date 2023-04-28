#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, int data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (queue->front == NULL && queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

int dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty. Dequeue operation failed.\n");
        return -1;
    }
    Node *node = queue->front;
    int data = node->data;
    queue->front = queue->front->next;
    free(node);
    return data;
}

int isQueueEmpty(Queue *queue)
{
    return (queue->front == NULL);
}

int main()
{
    Queue *queue = createQueue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    printf("Dequeue: %d\n", dequeue(queue));
    printf("Dequeue: %d\n", dequeue(queue));
    printf("Dequeue: %d\n", dequeue(queue));

    enqueue(queue, 4);
    // enqueue(queue, 5);
    // enqueue(queue, 6);

    // printf("Dequeue: %d\n", dequeue(queue));
    // printf("Dequeue: %d\n", dequeue(queue));
    // printf("Dequeue: %d\n", dequeue(queue));

    enqueue(queue, 10);
    if (queue->front->next == NULL)
    {
        printf("only one element");
    }

    free(queue);

    return 0;
}
