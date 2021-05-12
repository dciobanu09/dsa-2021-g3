#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

int givenArray[20], a, b;
int AddMap[20][20];

/*int max(int n1, int n2){
    if(n1 > n2)
    {
        return n1;
    }
    else
    {
        return n2;
    }
}

int min(int n1, int n2){
    if(n1 > n2)
    {
        return n1;
    }
    else
    {
        return n2;
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int findMaxFromArray(int sizeArray){
    int maximum = INT_MIN;
    for(int i = 0; i < sizeArray ; i++)
    {
        if(maximum < givenArray[i])
        {
            maximum = givenArray[i];
        }
    }
    return maximum;
}*/

int stepsNumberForAddition(int sizeOfArray, int* difference){
    int i, j, steps = 0, prevDifference, limit = 0;
    while(a != b && steps < 10)
    {
        for(i = limit; i < sizeOfArray; i++)
        {
            if(givenArray[i] == *difference)
            {
                steps++;
                return steps;
            }
        }
        steps++;
        a = a + givenArray[limit];
        prevDifference = *difference;
        *difference = *difference - givenArray[limit];
        if(*difference < 0)
        {
            *difference = prevDifference;
            limit ++;
        }
        for(i = limit; i < sizeOfArray; i++)
        {
            for(j = limit; j > i ; j++)
            {
                if(AddMap[i][j] == *difference)
                {
                    a = a + AddMap[i][j];
                    *difference = *difference - AddMap[i][j];
                    steps++;
                    steps++;
                    return steps;
                }
            }
        }
        for(i = limit; i < sizeOfArray; i++)
        {
            for(j = limit; j > i; j++)
            {
                if(AddMap[j][i] < *difference)
                {
                    *difference = *difference - AddMap[j][i];
                    a = a + AddMap[j][i];
                    steps++;
                    steps++;
                }
            }
        }
        if(AddMap[sizeOfArray-1][sizeOfArray-1] + a == b )
        {
            steps++;
            return steps;
        }
        else if(AddMap[sizeOfArray-1][sizeOfArray-1] + a > b)
        {
            return 0;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int i = 0;
    FILE* fIn= fopen(argv[1], "r");
    FILE* fOut = fopen(argv[2], "w");
    if(!fIn || !fOut || argc != 3)
    {
        printf("ERROR\n");
        exit(1);
    }
    fscanf(fIn, "%d", &a);
    fscanf(fIn, "%d", &b);
    while(fscanf(fIn, "%d", &givenArray[i]) != EOF)
    {
        i++;
    }
    int index, index2;
    for(index = 0; index < i; index++)
    {
        for(index2 = index + 1; index2 < i; index2++)
        {
            if(givenArray[index] < givenArray[index2])
            {
                int aux = givenArray[index];
                givenArray[index] = givenArray[index2];
                givenArray[index2] = aux;
            }
        }
    }
    for(index = 0; index < i; index++)
    {
        for(index2 = 0; index2 < i; index2++)
        {
            AddMap[index][index2] = givenArray[index] + givenArray[index2];
        }
    }
    int difference = b - a;


    printf("The number of needed steps using addition is: %d.\n", stepsNumberForAddition(i, &difference));
    fclose(fIn);
    fclose(fOut);
    return 0;
}
