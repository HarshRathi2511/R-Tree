#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point point;
typedef struct rectangle rectangle;
typedef struct Rnode Rnode;
typedef struct node node;
typedef struct Queue Queue;

node makeLeafNodes(int i);
node makenonLeafNode(Rnode *child);
Rnode *makeLeafRNodes(int l);
Rnode *makeRnode(bool isLeaf, bool isRoot);

void Resolver(Rnode *addrs[], int i);  //incomplete 
rectangle MinBoundRect(Rnode *rnode);

#define M 4
#define m 2
// change the names of these variables
point *A;
int n = 0;
struct rectangle
{
    float low_x;
    float low_y;
    float high_x;
    float high_y;
};
struct node
{
    rectangle mbr;
    Rnode *childpointer;
};
struct Rnode
{
    bool isLeaf;
    bool isRoot;
    int numChild; // number of elements in each rnode
    node childlist[M];
};
struct point
{
    float x;
    float y;
};

// Queue implementation in C
struct Queue
{
    int size;
    int front;
    int rear;
    Rnode **Q;
};
void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = malloc(q->size * sizeof(Rnode *));
}
void enqueue(struct Queue *q, Rnode *x)
{
    if (q->rear == q->size - 1)
        printf("Queue is Full");
    else
    {
        q->rear++;
        q->Q[q->rear] = x;
    }
}
Rnode *dequeue(struct Queue *q)
{
    Rnode *x = NULL;

    if (q->front == q->rear)
        return NULL;
    else
    {
        q->front++;
        x = q->Q[q->front];
    }
    return x;
}
// HELPER FUNCTIONS :- @neel @samarth edit according to requirements

float min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}
Rnode *makeLeafRNodes(int l)
{
    Rnode *rnode = makeRnode(true, false);
    int i = 0;
    for (i = l; i < min(l + M, n); i++)
    {
        node newnode = makeLeafNodes(i);
        rnode->childlist[i] = newnode;
    }
    rnode->numChild = i - l;
}
/*
    makes leaf nodes from the point array 
*/
node makeLeafNodes(int i)
{
    node newnode;
    newnode.childpointer = NULL;
    rectangle r;
    r.low_x = A[i].x;
    r.high_x = A[i].x;
    r.low_y = A[i].y;
    r.high_y = A[i].y;
    newnode.mbr = r;
    return newnode;
}
Rnode *makeRnode(bool isLeaf, bool isRoot)
{
    Rnode *rnode = (malloc)(sizeof(Rnode));
    if (isLeaf && isRoot)
        return NULL;
    rnode->isLeaf = isLeaf;
    rnode->isRoot = isRoot;
    rnode->numChild = 0;
    return rnode;
}
node makenonLeafNode(Rnode *child)
{
    node newnode;
    newnode.childpointer = child;
    newnode.mbr = MinBoundRect(child);
    return newnode;
}
void fillNonLeafRnode(Queue *childRnodes, Rnode *parent)
{
    int i = 0;
    for (i = 0; i < M; i++)
    {
        Rnode *child = dequeue(childRnodes); // if no child dequeue should give null;
        if (!child)
            break;
        node par = makenonLeafNode(child);
        parent->childlist[i] = par;
    }
    parent->numChild = i;
}


// MBR :- Testing left
rectangle MinBoundRect(Rnode *rnode)
{
    rectangle r = rnode->childlist[0].mbr;
    rectangle minbound = r;
    for (int i = 1; i < rnode->numChild; i++)
    {
        rectangle r = rnode->childlist[i].mbr;
        if (minbound.low_x > r.low_x)
            minbound.low_x = r.low_x;
        if (minbound.low_y > r.low_y)
            minbound.low_y = r.low_y;
        if (minbound.high_x < r.high_x)
            minbound.high_x = r.high_x;
        if (minbound.high_x < r.high_x)
            minbound.high_x = r.high_x;
    }
    return minbound;
}

// PREORDER TRAVERSAL
void preorder(Rnode *root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < root->numChild; i++)
    {
        // use a custom print function for the rectangle along with whether leaf or non leaf node
        printf("%f ", root->childlist[i].mbr.high_x);
        preorder(root->childlist[i].childpointer);
    }
}
//functions for mking the r tree 

// Rnode * createRtree(Queue * childRnodes)//initially pass queue of leafRnode Addresses
// {
//     Rnode * addrs[n];
//     int i = 0;
//     do{
//         Rnode * parent = malloc(sizeof(Rnode));
//         fillNonLeafRnode(childRnodes,parent);
//         if(parent ==NULL);break;
//         addrs[i++] = parent;
//     }while(true);
//         if(i==1) {
//         addrs[0]->isRoot = true;
//         return addrs[0];
//         }
//         if(addrs[i-1]->numChild < m)
//         Resolver(addrs,i);
//         for(int j=0;j<i;j++){
//            enqueue(childRnodes,addrs[i]);
//         }
//         return createRtree(childRnodes);
// }

// Queue * LeafRNodeAddresses(){
//     Queue * q;
//     q = malloc(sizeof(Queue));
//     Rnode * addrs[n];
//     int i=0,x=0;
//     for(i=0;i<n;i+=M){
//          addrs[x++] = makeLeafRNodes(i);
//     }
//  if(i>n)
//  addrs[x++] = makeLeafRNodes(i-M);
//  Resolver(addrs,x);
//  for(int j =0;j<x;j++){
//     enqueue(q,addrs[j]);
//  }
//  return q;

// }

// void Resolver(Rnode *addrs[],int i) implement it resolve the leaf nodes

// STR CODE :-

int LoadRectangles()
{
    FILE *fp = fopen("data.txt", "r");
    char buff[30];
    while (fgets(buff, 30, fp) != NULL)
        n++;
    A = malloc(n * sizeof(point));
    int i = 0;
    rewind(fp);
    while (fgets(buff, 30, fp) != NULL)
    {
        sscanf(buff, "%f %f", &A[i].x, &A[i].y);
        i++;
    }
    return n;
}

void swap(point *x, point *y)
{
    point temp = *x;
    *x = *y;
    *y = temp;
}

void Merge(int l, int mid, int h, int x)
{
    int i = l, j = mid + 1, k = l;
    point B[100];

    while (i <= mid && j <= h)
    {
        if (x == 1)
        {
            if (A[i].x < A[j].x)
                B[k++] = A[i++];
            else
                B[k++] = A[j++];
        }
        else if (x == 0)
        {
            if (A[i].y < A[j].y)
                B[k++] = A[i++];
            else
                B[k++] = A[j++];
        }
    }

    for (; i <= mid; i++)
        B[k++] = A[i];
    for (; j <= h; j++)
        B[k++] = A[j];

    for (i = l; i <= h; i++)
        A[i] = B[i];
}

void MergeSort(int l, int h, int x)
{
    int mid;
    if (l < h)
    {
        mid = (l + h) / 2;
        MergeSort(l, mid, x);
        MergeSort(mid + 1, h, x);
        Merge(l, mid, h, x);
    }
}

void STR()
{
    MergeSort(0, n - 1, 1);
    int p = ceil(n / M);
    int s = ceil(sqrt(p));
    for (int i = 0; i < n; i = i + s * M)
    {
        MergeSort(i, min(n - 1, i + s * M - 1), 0);
    }
}
void displayRectangles()
{
    for (int i = 0; i < n; i++)
    {
        printf("x:- %f  y:- %f \n", A[i].x, A[i].y);
    }
}
void main()
{
    int n = LoadRectangles();
    STR();
    displayRectangles();
}
