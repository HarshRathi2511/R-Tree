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
void displaySingleNode(node *node);
rectangle MinBoundRect(Rnode *rnode);
void printRecToCSV(rectangle mbr);

#define M 128

struct nodearray // array of nodearray which stores the size as well
{
    node *arr;
    int size;
};

// array of RNodes
struct Rnodearray
{
    Rnode **arr; // array of Rnode*
    int size;
};

// The below struct stores the node's contained rectangle and the bottom left and bottom right coordinates
struct rectangle
{
    float low_x;
    float low_y;
    float high_x;
    float high_y;
};
struct node
{
    rectangle mbr;       // rectangle contained in the node
    Rnode *childpointer; // pointer to the rnode i.e their children
};

// RNode is the basic unit of the RTree,and contains the array of child nodes
struct Rnode
{
    bool isLeaf;
    bool isRoot;
    int numChild;      // number of elements in each rnode
    node childlist[M]; // array of nodes contained in each rnode
};
// Point:- used to take in the (x,y) coordinate from the dataset
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

// creates the RNode from the grouped nodes
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
    if (child == NULL)
    {
        printf("child null\n");
    }
    if (child->childlist == NULL)
    {
        printf("childlist null\n");
    }

    node newnode;
    newnode.childpointer = child;
    newnode.mbr = MinBoundRect(child);
    return newnode;
}

void swap(point *x, point *y)
{
    point temp = *x;
    *x = *y;
    *y = temp;
}

// computes the centre of the rectangle
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
            if (centrei.x <= centrej.x)
                B[k++] = node_arr->arr[i++];
            else
                B[k++] = node_arr->arr[j++];
        }
        // sorted according to y coordinate
        else
        {
            if (centrei.y <= centrej.y)
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

// displays the node and its mbr:- used in preorder traversal
void displaySingleNode(node *node)
{
    if (node->childpointer == NULL)
    {
        // case of leaf nodes
        printf("Leaf  \t:- ");
        printf("(x,y):-(%.2f %.2f) \n", node->mbr.low_x, node->mbr.low_y);
    }
    else
    {
        printf("Internal:- ");
        printf("(low_x,low_y):-(%.2f %.2f),(high_x,high_y) (%.2f %.2f) \n", node->mbr.low_x, node->mbr.low_y, node->mbr.high_x, node->mbr.high_y);
    }
}
// utility function for printing the preorder traversal to a file to aid in python matlib graphs
void printRecToCSV(rectangle mbr)
{
    FILE *fp = fopen("rect_data.csv", "a");
    if (fp == NULL)
    {
        printf("File pointer not found\n");
    }
    // write abs()
    fprintf(fp, "%d,%d,%d,%d\n", (int)mbr.low_x, (int)mbr.low_y, (int)mbr.high_x - (int)mbr.low_x, (int)mbr.high_y - (int)mbr.low_y);
    fclose(fp);
}
//clears the contents of the file rect_data.csv 
void clearRectCSV()
{
    FILE *fp = fopen("rect_data.csv", "w"); // open the file in "write" mode to clear the contents of the file
    if (fp == NULL)
        return;
    fclose(fp); // close the file to delete its contents
}
// HELPER FUNCTIONS END .............................

/*
  The STR function takes an unordered array of nodes and packs them into a spatial index structure using the
   Sort-Tile-Recursive (STR) algorithm.
  The algorithm works by first sorting the rectangles by their x-coordinate and
   then partitioning them into s vertical slices. Each slice is then sorted by y-coordinate
   and packed into nodes.
 node_arr: An unordered array of nodes
 b: The maximum number of nodes in an Rnode
 */
void STR(nodearray *node_arr, int b)
{
    // Sort the nodes in ascending order according to their x coordinates
    MergeSort(node_arr, 0, node_arr->size - 1, true);

    // Calculate the number of leaf pages in the spatial index structure
    int p = ceil((float)node_arr->size / (float)b);

    // Calculate the number of vertical slices
    int s = ceil(sqrt(p));

    // Sort each slice in ascending order according to their y coordinates
    for (int i = 0; i < node_arr->size; i = i + s * b)
    {
        MergeSort(node_arr, i, min(node_arr->size - 1, i + s * b - 1), false);
    }
}

// MBR :- Computes the MBR for the given rectangle
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

//load the rectangles from the file data.txt 
nodearray LoadRectangles(char *filename)
{
    clearRectCSV(); // clears the file contents of rect_data.csv

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File pointer not found\n");
    }
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
    int i = 0;
    rewind(fp);
    //load the data from the file into the buffer variable and then into nodearray 
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

//Takes in the nodearray -> applies STR on it -> groups it into RNodes ->returns the RNodes 
Rnodearray *createRNodesForLevel(nodearray a, bool Leaf)
{
    // define and allocate:- rnode_arr
    Rnodearray *rnode_arr = malloc(sizeof(Rnodearray));
    rnode_arr->size = ceil((float)a.size / (float)M);
    rnode_arr->arr = malloc(sizeof(Rnode *) * rnode_arr->size);

    STR(&a, M);
    int x = 0; // counts the iterations for rnode_arr
    for (int i = 0; i < a.size; i += M)
    {
        // grouped node 
        nodearray grouped_nodes;
        grouped_nodes.arr = malloc(M * sizeof(node));
        // The size of this array is set to the minimum value between M and the remaining number
        // of nodes in the input node array.
        grouped_nodes.size = min(M, a.size - i);
        //A nested for loop is used to copy a group of nodes from the input node array to the new node array.
        for (int j = 0; j < M && (i + j) < a.size; j++)
        {
            grouped_nodes.arr[j] = a.arr[i + j];
        }

        // create r-nodes for the grouepd nodes
        Rnode *r1 = createRNodes(grouped_nodes, Leaf);
        rnode_arr->arr[x] = r1;

        // dont change
        x++;
    }
    //After all iterations are completed, return to the created rnode_arr.
    return rnode_arr;
}

//The main code to create the RTree ,and returns the root RNode of the tree on completions 
Rnode *createTree(Rnodearray *rnode_arr)
{
    // Base Case:- when the rnodes in the input array are one :- i.e ROOT rnode
    if (rnode_arr->size == 1)
    {
        return rnode_arr->arr[0];
    }
    // Create the nodearray of the parent nodes
    nodearray created_parent_nodes;
    created_parent_nodes.arr = malloc(rnode_arr->size * sizeof(node));
    created_parent_nodes.size = rnode_arr->size;

    for (int i = 0; i < rnode_arr->size; i++)
    {
        // null/debug checks
        if (rnode_arr->arr[i] == NULL)
        {
            printf("rnode iteration null in %d\n", i);
        }
        // makes parent node from rnode
        created_parent_nodes.arr[i] = makenonLeafNode(rnode_arr->arr[i]);
    }

    // convert the array of parent nodes and group them into rnodes
    Rnodearray *created_parent_rnodes = createRNodesForLevel(created_parent_nodes, false);

    // free to avoid memory leaks
    free(rnode_arr->arr);
    free(rnode_arr);
    free(created_parent_nodes.arr);

    // recursive call to create the nodes for the next level until the base case reached i.e only the root remains 
    createTree(created_parent_rnodes);
}

// Preorder Traversal of the RTree
void preorder(Rnode *root)
{   
    //Base Case
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < root->numChild; i++)
    {
        // use a custom print function for the rectangle along with whether leaf or non leaf node
        displaySingleNode(&root->childlist[i]);
        //prints the mbrs to the rect_data.csv file to aid in matplotlib graph plotting 
        printRecToCSV(root->childlist[i].mbr);
        //recursive call to the childlist of the current RNodes contained Nodes 
        preorder(root->childlist[i].childpointer);
    }
}

void main()
{
    //the file from which the dataset loaded is passed in this function 
    nodearray node_arr = LoadRectangles("large_dataset.txt");
    //creates the rnodes for the base level and passed into the createTree function 
    Rnodearray *rnode_arr = createRNodesForLevel(node_arr, true);
    //creates the tree from the ground level of RNodes and the subsequent levels and returns the root 
    Rnode *root = createTree(rnode_arr);
    //Preorder traversal of the created R Tree 
    preorder(root);
}
