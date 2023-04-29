#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point point;
typedef struct rectangle rectangle;
typedef struct Rnode Rnode;
typedef struct node node;
typedef struct Queue Queue;
typedef struct nodearray nodearray;

node makeLeafNodes(rectangle rect);
node makenonLeafNode(Rnode *child);
Rnode *createRNodes(nodearray narr, bool Leaf);
Rnode *makeRnode(bool isLeaf, bool isRoot);
void displayNodeArray(nodearray node_arr);

// void Resolver(Rnode *addrs[], int i); // incomplete
rectangle MinBoundRect(Rnode *rnode);

#define M 4
#define m 2

struct nodearray
{
    node *arr;
    int size;
};

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
    if ((q->rear + 1) % (q->size) == q->front)
        printf("Queue is Full");
    else
    {
        q->rear = (q->rear + 1) % (q->size);
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
        q->front = (q->front + 1) % (q->size);
        x = q->Q[q->front];
    }
    return x;
}
int qsize(struct Queue *q)
{
    if (q->rear >= q->front)
    {
        return q->rear - q->front + 1;
    }
    else
    {
        return q->size - (q->front - q->rear - 1);
    }
}
// HELPER FUNCTIONS :- @neel @samarth edit according to requirements

float min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}
Rnode *createRNodes(nodearray narr, bool Leaf)
{
    Rnode *rnode = makeRnode(Leaf, false);
    int i = 0;
    for (i = 0; i < narr.size; i++)
    {
        node newnode = narr.arr[i];
        rnode->childlist[i] = newnode;
    }
    rnode->numChild = narr.size;
}
// /*
//     makes leaf nodes from the point array
// */
node makeLeafNodes(rectangle rect)
{
    node newnode;
    newnode.childpointer = NULL;
    newnode.mbr = rect;
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
// void fillNonLeafRnode(Queue *childRnodes, Rnode *parent)
// {
//     int i = 0;
//     for (i = 0; i < M; i++)
//     {
//         Rnode *child = dequeue(childRnodes); // if no child dequeue should give null;
//         if (!child)
//             break;
//         node par = makenonLeafNode(child);
//         parent->childlist[i] = par;
//     }
//     parent->numChild = i;
// }

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
// functions for mking the r tree

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

// correct
nodearray LoadRectangles()
{

    FILE *fp = fopen("data.txt", "r");
    char buff[30];
    int n = 0;
    while (fgets(buff, 30, fp) != NULL)
    {
        n++;
    }

    // create nodearray
    nodearray nodearr;
    node *arr = malloc(n * sizeof(node));
    nodearr.arr = arr;
    nodearr.size = n;
    //
    int i = 0;
    rewind(fp);
    while (fgets(buff, 30, fp) != NULL)
    {
        float x = 0, y = 0;
        sscanf(buff, "%f %f", &x, &y);
        rectangle r;
        r.low_x = r.high_x = x;
        r.low_y = r.high_y = y;
        arr[i] = makeLeafNodes(r);
        i++;
    }
    fclose(fp);

    return nodearr;
}

void swap(point *x, point *y)
{
    point temp = *x;
    *x = *y;
    *y = temp;
}

point computeCentre(rectangle rect)
{
    point p;
    p.x = (rect.low_x + rect.high_x) / 2.0;
    p.y = (rect.low_y + rect.high_y) / 2.0;
    return p;
}
// pass the input node array in this function
void Merge(nodearray *node_arr, int l, int mid, int h, bool xflag)
{
    int i = l, j = mid + 1, k = l;
    // change this into a rectangle/node array
    int n = node_arr->size;
    node B[n]; // check

    while (i <= mid && j <= h)
    {
        point centrei = computeCentre(node_arr->arr[i].mbr);
        point centrej = computeCentre(node_arr->arr[j].mbr);

        // sorted according to x coordinate
        if (xflag)
        {
            if (centrei.x < centrej.x)
                B[k++] = node_arr->arr[i++];
            else
                B[k++] = node_arr->arr[j++];
        }
        // sorted according to y coordinate
        else
        {
            if (centrei.y < centrej.y)
                B[k++] = node_arr->arr[i++];
            else
                B[k++] = node_arr->arr[j++];
        }
    }

    for (; i <= mid; i++)
        B[k++] = node_arr->arr[i];
    for (; j <= h; j++)
        B[k++] = node_arr->arr[j];

    for (i = l; i <= h; i++)
        node_arr->arr[i] = B[i];
}

// pass an input node array in it which is to be sorted
void MergeSort(nodearray *node_arr, int l, int h, bool xflag)
{
    int mid = 0;
    if (l < h)
    {
        mid = (l + h) / 2;
        MergeSort(node_arr, l, mid, xflag);
        MergeSort(node_arr, mid + 1, h, xflag);
        Merge(node_arr, l, mid, h, xflag);
    }
}

// change this to the below signature :-
//  node str(node* arr){
void STR(nodearray *node_arr, int b)
{
    MergeSort(node_arr, 0, node_arr->size - 1, true); // should return an node array

    int p = ceil((float)node_arr->size / (float)b);
    int s = ceil(sqrt(p));
    for (int i = 0; i < node_arr->size; i = i + s * b)
    {
        MergeSort(node_arr, i, min(node_arr->size - 1, i + s * b - 1), false);
    }
    displayNodeArray(*node_arr);
}

// function to print points loaded from file
void printRectangle(rectangle rect)
{
    point p = computeCentre(rect);
    printf("%.2f %.2f \n", p.x, p.y);
}
void displayNodeArray(nodearray node_arr)
{
    printf("size of node arr :- %d \n\n", node_arr.size);
    for (int i = 0; i < node_arr.size; i++)
    {
        printRectangle(node_arr.arr[i].mbr);
    }
}

Queue *createRNodesForLevel(nodearray a, bool Leaf)
{
    Queue *q1;
    create(q1, a.size);
    int i;

    for (i = 0; i < (a.size - 2 * M); i += M)
    {
        {
            nodearray n1;
            node *a1 = malloc(M * sizeof(node));
            n1.arr = a1;
            n1.size = M;
            for (int j = 0; j < M; j++)
            {
                n1.arr[j] = a.arr[i + j];
            }

            Rnode *r1 = createRNodes(n1, Leaf);
            enqueue(q1, r1);
            free(a1);
        }
    }
    // making a new nodearray for remaining less than 2*M nodes
    nodearray n2;
    node *a2 = malloc(a.size - i * sizeof(node));
    n2.arr = a2;
    n2.size = a.size - i;
    for (int j = 0; j < n2.size; j++)
    {
        n2.arr[j] = a.arr[i + j];
    }
    // sending remaining < 2*M nodes to STR
    int secondlastsize = M - (m - (a.size - i - M));
    STR(&n2, secondlastsize);

    // creating RNodes for 2nd last group of nodes
    nodearray n1;
    node *a1 = malloc(secondlastsize * sizeof(node));
    n1.arr = a1;
    n1.size = secondlastsize;
    int j;
    for (j = 0; j < secondlastsize; j++)
    {
        n1.arr[j] = n2.arr[j];
    }
    Rnode *temp_r1 = createRNodes(n1, Leaf);
    enqueue(q1, temp_r1);
    free(a1);
    // creating Rnode for last m nodes
    nodearray n4;
    node *temp2 = malloc(m * sizeof(node));
    n4.arr = temp2;
    n4.size = m;
    for (int k = 0; k < m; k++)
    {
        n4.arr[k] = n2.arr[j + k];
    }
    Rnode *temp_r2 = createRNodes(n4, Leaf);
    enqueue(q1, temp_r2);
    free(temp2);
    return q1;
}

Rnode *createTree(Queue *q)
{
    int Qsize = qsize(q);
    if (Qsize == 1)
    {
        return dequeue(q);
    }
    nodearray n3;
    node *a3 = malloc(Qsize * sizeof(node));
    n3.arr = a3;
    n3.size = Qsize;
    for (int i = 0; i < Qsize; i++)
    {
        // makes parent node from rnode
        node n = makenonLeafNode(dequeue(q));
        n3.arr[i] = n;
    }
    Queue *queue = createRNodesForLevel(n3, false);
    createTree(queue);
}

void main()
{
    // inital loading from the file
    nodearray node_arr = LoadRectangles();
    displayNodeArray(node_arr);
    STR(&node_arr, M);
    Rnode *root = createTree(createRNodesForLevel(node_arr, true));
    // preorder(root);
}
