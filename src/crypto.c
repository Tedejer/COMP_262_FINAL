#include "crypto.h"

// to compile
// do gcc -fopenmp crypto.c -lm
// also you need to have the header file in the directory

// A function to print all prime factors of a given number n 
int primeFactors(int n, int *factored) 
{ 
	int p = 0;
	
    // Print the number of 2s that divide n
    #pragma omp parallel shared(n,p,factored) default(none)
    {
		
        #pragma omp single
        while (n %2 == 0)
        { 
            printf("%d ", 2); 
            n = n/2;
			factored[p] = n;
			p++;
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
				factored[p] = n;
				p++;
            } 
        }

        // This condition is to handle the case when n  
        // is a prime number greater than 2 
        #pragma omp single
        if (n > 2){ 
            printf ("%d ", n);
			factored[p] = n;
			p++;
        } 
    }
	
	return p;
}

  
/* Driver program to test above function */
int main() 
{ 

    int number,p;
	int factored[10];

    printf("Enter a number: ");
    scanf("%d,",&number);
    printf("The prime factors for %d are:\n",number);

	// CALCULATION
    clock_t begin = clock();
    p = primeFactors(number,factored);
    clock_t end = clock();

    double time_spent = (double)(end - begin);
	
	// STORE VALUES TO FILE
    FILE *fpx;
    fpx = fopen("Output.txt","w");
    
	for(int i = 0; i <= p; i++) 
	{
		
		fprintf(fpx, "%d,", factored[i]);
		fprintf(fpx,"\n");
		
		// PRINT OUT FACTORED ARRAY FOR DEBUG
		printf("\n%d ",factored[i]);

	}
	
    
    fclose(fpx);
	
    printf("\nThe execution time for this program took: %.1f seconds",time_spent);
	printf("\n The size of p is %d",p);
    printf("\n");
    return 0; 
}
