#include <stdio.h>
#include <stdlib.h>

int leastCommonMultiple(int n1, int n2)
{
    int maximum;
    if(n1 > n2)
    {
        maximum = n1;
    }
    else
    {
        maximum = n2;
    }
    while(1)
    {
        if(maximum % n1 == 0 && maximum % n2 == 0)
            break;
        ++maximum;
    }
    return maximum;
}

int greatestCommonDivisor(int n1, int n2)
{
    int gcd, i;
    for(i=1; i <= n1 && i <= n2; ++i)
    {
       if(n1%i==0 && n2%i==0)
       {
           gcd = i;
       }
    }
    return gcd;
}

int ceil(int numerator, int denominator)
{
    return denominator/numerator+1;
}

int fractionCalculator(int numerator, int denominator)
{
    if(numerator == 1)
    {
        printf(" 1/%d\n", denominator);
        return 0;
    }
    else
    {
        int inverse = ceil(numerator, denominator);
        printf(" 1/%d +", inverse);
        int newDenominator = leastCommonMultiple(denominator, inverse);
        int newNumerator = numerator * leastCommonMultiple(denominator, inverse) / denominator - 1*leastCommonMultiple(denominator,inverse) / inverse;
        return fractionCalculator(newNumerator, newDenominator);
    }
}

int main()
{
    int numerator, denominator;
    printf("Enter the numerator: ");
    scanf("%d", &numerator);
    printf("Enter the denominator: ");
    scanf("%d", &denominator);
    printf("You have entered: %d/%d\n", numerator, denominator);
    fractionCalculator(numerator, denominator);
    return 0;
}
