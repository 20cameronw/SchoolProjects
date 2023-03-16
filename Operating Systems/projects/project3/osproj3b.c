/**
 * Cameron Weston
 * CSC 360 
 * Project 3b: Fibonacci series using threads
 * 9/18/2022
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FIBS 50

//prototypes
void *compute_fib(void *);

//global variables
int fiboNumbers[50] = {0};
int nFibo;

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    //init attributes with default params
    pthread_attr_init(&attr);

    //save the command line arg globally
    nFibo = atoi(argv[1]);

    pthread_create(&tid, &attr, compute_fib, &nFibo);

    //wait for the thread to exit
    pthread_join(tid, NULL);


    printf("The fibonacci numbers to n: %d\n", nFibo);
    for (int i = 0; i < nFibo; i++)
    {
        printf("%d ", fiboNumbers[i]);
    }
    printf("\n");

    return 0;
}

void *compute_fib(void *s)
{
    for (int i = 0; i < nFibo; i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
        {
            fiboNumbers[i] = 1;
        }
        else
        {
            fiboNumbers[i] = fiboNumbers[i-1] + fiboNumbers[i-2];
        }
    }
    pthread_exit(0);
    
}