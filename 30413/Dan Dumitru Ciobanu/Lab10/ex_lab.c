#include <stdio.h>
#include <stdlib.h>

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

int findMinimumCost(int *matrix, int auxRows, int auxCols){
    int aux[auxRows][auxCols];
    int i,j;
    for( i = 0; i < auxRows; i++)
    {
        for( j = 0; j < auxCols; j++)
        {
            aux[i][j] = matrix + i + j;
        }
        if(i == 0 && j > 0)
        {
            aux[0][j] += aux[0][j-1];
        }
        else if(j == 0 && i > 0)
        {
            aux[i][0] += aux[i-1][0];
        }
        else if(i > 0 && j > 0)
        {
            aux[i][j] += min(aux[i-1][j], aux[i][j-1]);
        }
    }
    return aux[auxRows-1][auxCols-1];
}

int main() {
    int rows, cols;
    printf("Enter the desired sizes:\n");
    printf("rows: ");
    scanf("%d", &rows);
    printf("columns: ");
    scanf("%d", &cols);
    int* matrix = (int*)malloc(rows * cols * sizeof(int));
    int i , j;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            printf("Insert at position: %d, %d: \n", i, j);
            scanf("%d", matrix + i + j );
        }
    }
    for(i = 0; i < rows * cols; i++)
    {
        int* current = matrix + i;
        free(current);
    }
    printf("The minimum cost traversal of the matrix is: %d.", findMinimumCost(matrix, rows, cols));
    return 0;
}
