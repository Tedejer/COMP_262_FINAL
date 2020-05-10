
#include "crypto.h"

// A function to print all prime factors of a given number n 
void primeFactors(int n) 
{ 
    // Print the number of 2s that divide n 
    #pragma omp parallel
    {
        #pragma omp single
        while (n%2 == 0) 
        { 
            printf("%d ", 2); 
            n = n/2; 
        } 
      
        // n must be odd at this point.  So we can skip  
        // one element (Note i = i +2) 
        #pragma omp single 
        for (int i = 3; i <= sqrt(n); i = i+2) 
        { 
            // While i divides n, print i and divide n 
            while (n%i == 0) 
            { 
                printf("%d ", i); 
                n = n/i; 
            } 
        }

        // This condition is to handle the case when n  
        // is a prime number greater than 2 
        #pragma omp single
        if (n > 2){ 
            printf ("%d ", n);
        } 
    }
}

  
/* Driver program to test above function */
int main() 
{ 

    int number; 

    printf("Enter a number: ");
    scanf("%d,",&number);

    clock_t begin = clock();

    printf("The prime factors for %d are:\n",number);
    primeFactors(number); 

    clock_t end = clock();
    double time_spent = (double)(end - begin); 

    printf("\nThe execution time for this program took: %.1f seconds",time_spent);

    printf("\n");
    return 0; 
}
