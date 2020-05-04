#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    int i, j, num, isPrime;

    printf("Enter any number to print Prime factors: ");
    scanf("%d", &num);
    printf("All Prime Factors of %d are: \n", num);

    clock_t begin = clock();
    #pragma omp parallel
    {
        // variables local to threads
        int id;
        double Pbegin,Pend;

        id = omp_get_thread_num();
        Pbegin = omp_get_wtime();

        #pragma omp for
        for (i = 2; i <= num; i++)
        {

            if (num % i == 0)
            {

                isPrime = 1;
                for (j = 2; j <= i / 2; j++)
                {
                    if (i % j == 0) {
                        isPrime = 0;
                        break;
                    }
                }

                if (isPrime == 1)
                {
                    printf("%d ", i);
                }
            }
        }

        printf("\n");
        Pend = omp_get_wtime();
        printf("Thread(%d) finished in %f seconds \n", id, Pend - Pbegin);
    }

    clock_t end = clock();
    double time = (double)(end - begin);

    printf("\nProgram executed in: %f seconds\n", time);

    return 0;
}