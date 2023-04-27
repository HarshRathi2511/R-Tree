#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct point point;
typedef struct rectangle rectangle;
typedef struct Rnode Rnode;
typedef struct node node;
#define M  2
#define m  M/2
struct rectangle{
    float low_x;
    float low_y;
    float high_x;
    float high_y;
};
struct node{
    rectangle mbr;
    Rnode * childpointer;
};
struct Rnode{
    int isLeaf;
    node childlist[M];
};
struct point
{
    float x;
    float y;
};
int min(float a,float b){
    if(a>b)
    return b;
    return a;
}
point * A;
int n=0;
int LoadRectangles(){
    FILE * fp = fopen("data.txt","r");
    char buff[30];
    while(fgets(buff,30,fp)!=NULL)
    n++;
    A = malloc(n*sizeof(point));
    int i=0;
    rewind(fp);
    while(fgets(buff,30,fp)!=NULL)
    {
      sscanf(buff, "%d %d", &A[i].x, &A[i].y);
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

void Merge(int l, int mid, int h,int x)
{
    int i = l, j = mid + 1, k = l;
    point B[100];

    while (i <= mid && j <= h)
    {
    if(x==1){
          if (A[i].x < A[j].x)
            B[k++] = A[i++];
        else
            B[k++] = A[j++];
    }
    else if(x==0){
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

void MergeSort(int l, int  h,int x)
{
    int mid;
    if (l < h)
    {
        mid = (l + h) / 2;
        MergeSort(l, mid,x);
        MergeSort(mid + 1, h,x);
        Merge(l, mid, h,x);
    }
}

void STR()
{
   MergeSort(0,n-1,1);
   int b = 2;
   int p = ceil(n/2);
   int s = ceil(sqrt(p));
   for(int i=0;i<n;i=i+s*b){
      MergeSort(i,min(n-1,i+s*b-1),0);
   }
}
void displayRectangles(){
    for(int i=0;i<n;i++){
        printf("%d %d \n",A[i].x,A[i].y);
    }
}
void main(){
    int n = LoadRectangles();
    STR();
    displayRectangles();

}
