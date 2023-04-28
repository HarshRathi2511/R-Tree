// #include "main.h"

// struct Queue
// {
//     int size;
//     int front;
//     int rear;
//     Rnode **Q;
// };
// void create(struct Queue *q, int size)
// {
//     q->size = size;
//     q->front = q->rear = -1;
//     q->Q = malloc(q->size * sizeof(Rnode *));
// }
// void enqueue(struct Queue *q, Rnode *x)
// {
//     if (q->rear == q->size - 1)
//         printf("Queue is Full");
//     else
//     {
//         q->rear++;
//         q->Q[q->rear] = x;
//     }
// }
// Rnode *dequeue(struct Queue *q)
// {
//     Rnode *x = NULL;

//     if (q->front == q->rear)
//         return NULL;
//     else
//     {
//         q->front++;
//         x = q->Q[q->front];
//     }
//     return x;
// }