#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int givenArray[100];

int maxOf2(int n1, int n2){
    if(n1 > n2)
    {
        return n1;
    }
    else
    {
        return n2;
    }
}

int findMaximumSum(int left, int right){
    if(left == right)
    {
        return givenArray[right];
    }
    int middle = (left + right) / 2;
    int sum = 0;
    int leftMax = INT_MIN;
    int rightMax = INT_MIN;
    int maxOfLeftAndRight;
    for(int i = middle; i >= left; i--)
    {
        sum = sum + givenArray[i];
        if(sum > leftMax)
        {
            leftMax = sum;
        }
    }
    sum = 0;
    for(int i = middle + 1; i <= right; i++)
    {
        sum = sum + givenArray[i];
        if(sum > rightMax)
        {
            rightMax = sum;
        }
    }
    maxOfLeftAndRight = maxOf2(findMaximumSum(left, middle), findMaximumSum(middle + 1, right));
    return maxOf2(maxOfLeftAndRight, leftMax + rightMax);
}

int main(int argc, char* argv[]) {
    FILE* fIn = fopen(argv[1], "r");
    FILE* fOut = fopen(argv[2], "w");
    if(!fIn || !fOut || argc != 3)
    {
        fprintf(fOut, "ERROR!\n");
        exit(1);
    }
    int nrOfInitElements, i;
    fscanf(fIn, "%d", &nrOfInitElements);
    for(i = 0; i<nrOfInitElements; i++)
    {
        fscanf(fIn, " %d", &givenArray[i]);
    }
    fprintf(fOut, "The biggest contiguous sum in the given array is %d .\n", findMaximumSum(0, nrOfInitElements - 1));
    fclose(fIn);
    fclose(fOut);
    return 0;
}
