#include <stdio.h>
#include <stdlib.h>

int numberOfVectorElements;
int min = 1000000;
int v[1000];
void findMinOperations(int v[], int i, int k, int op)
{

    if(k == 0 && i < numberOfVectorElements)
    {
        if(op < min )
        {
            min = op;
        }
        return;
    }
    if(i >= numberOfVectorElements )
    {
        return;
    }
    findMinOperations(v, i + 1, k, op);
    findMinOperations(v, i + 1, k - v[i], op + 1);
    findMinOperations(v, i + 1, k + v[i], op + 1);
}
int main(int argc, char **argv)
{
    int a, b;
    FILE* fi;
    FILE* fo;
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "w");
    fscanf(fi, "%d%d", &a, &b);
    numberOfVectorElements = 0;
    while(fscanf(fi, "%d", &v[numberOfVectorElements]) != EOF)
    {
        numberOfVectorElements++;
    }
    findMinOperations(v, 0, b-a, 0);

    if( min == 1000000 )
    {
        fprintf(fo,"No solutions");
    }
    else
    {
        fprintf(fo,"The minimum number of operations is: %d", min);
    }
    return 0;
}