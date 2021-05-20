#include <stdio.h>
#include <stdlib.h>

int x[3] = {1, 1, 0};
int y[3] = {0, 1, 1};
int min(int n1, int n2){
    if(n1 > n2)
    {
        return n2;
    }
    else
    {
        return n1;
    }
}

int findMinimumSteps(int *matrix, int auxRows, int auxCols){

}

int main() {
    int rows, cols;
    printf("Enter the desired sizes:\n");
    printf("rows: ");
    scanf("%d", &rows);
    printf("columns: ");
    scanf("%d", &cols);
    int* matrix = (int*)malloc(rows * cols * sizeof(int));
    printf("The minimum cost traversal of the matrix is: %d.", findMinimumSteps(matrix, rows, cols));
    return 0;
}
