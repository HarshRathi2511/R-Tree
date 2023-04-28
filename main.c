#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct point point;
typedef struct rectangle rectangle;
typedef struct Rnode Rnode;
typedef struct node node;
node  makeLeafNodes(int i);
#define M 4
#define m 2
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
    int numChild;
    node childlist[M];
};
struct point
{
    float x;
    float y;
};
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
Rnode *makeNonLeafRnode(bool isLeaf, bool isRoot)
{
    Rnode *rnode = (malloc)(sizeof(Rnode));
    if (isLeaf && isRoot)
        return NULL;
    rnode->isLeaf = isLeaf;
    rnode->isRoot = isRoot;
    rnode->numChild = 0;
    return rnode;
}
Rnode * prev;//set NULL before calling
// void preorder(Rnode *root) {
//     if (root == NULL) {
//         return;
//     }
//    for (int i = 0; i < root->numChildren; i++) {
//         printf("%f ", root->childlist[i].mbr);
//         preorder(root->childlist[i].childpointer);
//     }
// }
// void fillNonLeafRnode(Queue childRnodes,Rnode *parent){
//     for(int i=0;i<M;i++){
//         Rnode * child = deque(childRnodes);
//         if(!child)break;
//         node  par = makenonLeafNode(child);
//         parent->childlist[i]=par;
//     }
//          parent->numChild = i;
// } 
node makenonLeafNode(Rnode *child)
{
    node newnode;
    newnode.childpointer = child;
    newnode.mbr = MinBoundRect(child);
}
float min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}

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
Rnode * makeLeafRNodes(int l){
    Rnode * rnode = createRnode(true,false);
    int i =0;
    for( i=l;i<min(l+M,n);i++){
        node newnode = makeLeafNodes(i);
        rnode->childlist[i] = newnode;
    }
    rnode->numChild = i-l;

}
node makeLeafNodes(int i){
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
void STR()
{
    MergeSort(0, n - 1, 1);
    int p = ceil(n/M);
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
        printf("%f %f \n", A[i].x, A[i].y);
    }
}
void main()
{
    int n = LoadRectangles();
    STR();
    displayRectangles();
}