#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point point;
typedef struct rectangle rectangle;
typedef struct Rnode Rnode;
typedef struct node node;
typedef struct nodearray nodearray;
typedef struct Rnodearray Rnodearray;

node makeLeafNodes(rectangle rect);
node makenonLeafNode(Rnode *child);
Rnode *createRNodes(nodearray narr, bool Leaf);
Rnode *makeRnode(bool isLeaf, bool isRoot);
void displayNodeArray(nodearray node_arr);
void printRectangle(rectangle rect);

// void Resolver(Rnode *addrs[], int i); // incomplete
rectangle MinBoundRect(Rnode *rnode);

#define M 4
#define m 2

struct nodearray
{
    node *arr;
    int size;
};

struct Rnodearray
{
    Rnode **arr; // array of Rnode*
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

// HELPER FUNCTIONS :- 

float min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}
Rnode *createRNodes(nodearray node_arr, bool Leaf)
{
    Rnode *rnode = makeRnode(Leaf, false);
    int i = 0;
    for (i = 0; i < node_arr.size; i++)
    {
        node newnode = node_arr.arr[i];
        rnode->childlist[i] = newnode;
    }
    rnode->numChild = node_arr.size;
    return rnode;
}
/*
    makes leaf nodes from the point array
*/
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

void printRNodeAndElements(Rnode *rnode)
{
    for (int i = 0; i < rnode->numChild; i++)
    {
        printRectangle(rnode->childlist[i].mbr);
    }
    printf("....\n");
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
        if (minbound.high_y < r.high_y)
            minbound.high_y = r.high_y;
    }
    return minbound;
}

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
}

// function to print points loaded from file
void printRectangle(rectangle rect)
{
    // point p = computeCentre(rect);
    printf("%.2f %.2f %.2f %.2f \n", rect.low_x, rect.high_x, rect.low_y, rect.high_y);
}
void displayNodeArray(nodearray node_arr)
{
    for (int i = 0; i < node_arr.size; i++)
    {
        printRectangle(node_arr.arr[i].mbr);
    }
}

Rnodearray *createRNodesForLevel(nodearray a, bool Leaf)
{
    // define the rnode_arr
    Rnodearray *rnode_arr = malloc(sizeof(Rnodearray));
    rnode_arr->size = a.size / M + 1;
    rnode_arr->arr = malloc(sizeof(Rnode *) * rnode_arr->size);

    STR(&a, M);
    int x = 0;
    for (int i = 0; i < a.size; i += M)
    {
        // grouped node
        nodearray grouped_nodes;
        grouped_nodes.arr = malloc(M * sizeof(node));

        grouped_nodes.size = min(M, a.size - i);

        for (int j = 0; j < M && (i + j) < a.size; j++) // check condition
        {
            grouped_nodes.arr[j] = a.arr[i + j];
            // printf("%f\n",grouped_nodes.arr[j].mbr.low_x);
        }

        Rnode *r1 = createRNodes(grouped_nodes, Leaf);
        rnode_arr->arr[x] = r1;

        // debug vals
        //  printRNodeAndElements(rnode_arr->arr[i]);

        // dont change
        x++;
    }
    return rnode_arr;
}

Rnode *createTree(Rnodearray *rnode_arr)
{
    if (rnode_arr->size == 1)
    {
        return rnode_arr->arr[0];
    }
    printf("rnode input size:- %d\n", rnode_arr->size);
    nodearray created_parent_nodes;
    created_parent_nodes.arr = malloc(rnode_arr->size * sizeof(node));
    created_parent_nodes.size = rnode_arr->size;

    for (int i = 0; i < rnode_arr->size; i++)
    {
        // makes parent node from rnode
        created_parent_nodes.arr[i] = makenonLeafNode(rnode_arr->arr[i]);
        // printf("%f ", created_parent_nodes.arr[i].mbr.low_x);
        // printRectangle(created_parent_nodes.arr[i].mbr);
    }
    Rnodearray *created_parent_rnodes = createRNodesForLevel(created_parent_nodes, false);
    printf("rnode op size:- %d\n\n\n", created_parent_rnodes->size);

    createTree(created_parent_rnodes);
}

// PREORDER TRAVERSAL
static int count =0;
void preorder(Rnode *root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < root->numChild; i++)
    {
        // use a custom print function for the rectangle along with whether leaf or non leaf node
        printRectangle(root->childlist[i].mbr);
        preorder(root->childlist[i].childpointer);
    }
}

void main()
{
    // inital loading from the file
    nodearray node_arr = LoadRectangles();
    // displayNodeArray(node_arr);

    Rnodearray *rnode_arr = createRNodesForLevel(node_arr, true);

    // for(int i=0;i<rnode_arr->size;i++){
    //     printRNodeAndElements(rnode_arr->arr[i]);
    // }

    // printf("%d",rnode_arr->size);

    Rnode *root = createTree(rnode_arr);
    if (root)
    {
        printRNodeAndElements(root);
    }
    preorder(root);
}