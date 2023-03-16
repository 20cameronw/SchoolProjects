
/**
 * 
 * Cameron Weston
 * CSC 360 Operating Systems
 * Instructor: Dr. Siming Liu
 * Project 4:  Process Synchronization Using Pthreads
 * Tuesday, September 27, 2022
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cmath>

//prototypes
void *consumer(void *param);
void *producer(void *param);
void printSnapshot();
bool isPrime(int);


//init global variables to store the command line arguments
int simulationTime = 0;
int numProducers = 0;
int numConsumers = 0;
int maxThreadSleepTime = 0;
bool outputBufSnapshots = false;

//threads use this global data
buffer_item buffers[BUFFER_SIZE] = {0};
int in = 0;
int out = 0;
int counter = 0;
pthread_mutex_t mutex;
sem_t full;
sem_t empty; 

bool threadsRunning = true;
int itemsProduced = 0;
int itemsConsumed = 0;


//struct to hold data about specific instances of threads
typedef struct {
    long tid;
    int itemsMoved;
} thread_data;


/**
  main()
  Get command line arguments
  Initialize buffer
  Create producer thread(s)
  Create consumer thread(s)
  Sleep
  Join Threads
  Display Statistics
  Exit

  Command Line arguments: 
    The length of time the main thread is to sleep before terminating (simulation length in seconds)
    The maximum length of time the producer and consumer threads will sleep prior to producing or consuming a buffer_item
    The number of producer threads
    The number of consumer threads
    A "yes" or "no" to output the individual buffer snapshots for each item produced and consumed
*/

int main(int argc, char* argv[])
{
    int totalThreads;
    int ii;

    //check for correct number of command line arguments
    if (argc != 6)
    {
        printf("Must pass 6 command line arguments in the following format:\n");
        printf("filename int int int int (yes or no)\n");
        return 1;
    }
    //get command line arguments
    //no input validation!!
    simulationTime = atoi(argv[1]);
    maxThreadSleepTime = atoi(argv[2]);
    numProducers = atoi(argv[3]);
    numConsumers = atoi(argv[4]);
    if (strcmp(argv[5], "no"))
      outputBufSnapshots = true;
    else
      outputBufSnapshots = false;
    totalThreads = numProducers + numConsumers;
    
    //initialize buffer
    pthread_mutex_init( &mutex, NULL );
    sem_init( &full, 0, 0);
    sem_init( &empty, 0, BUFFER_SIZE);

    //initialize threads
    pthread_t threads[totalThreads];
    thread_data thread_datas[totalThreads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    //create producer threads
    for (ii = 0; ii < numProducers; ii++)
    {
        pthread_create(&threads[ii], &attr, producer, (void *)&thread_datas[ii]);
        thread_datas[ii].tid = threads[ii];
        thread_datas[ii].itemsMoved = 0;
        //printf("Created producer thread %d\n", threads[ii]);
    }

    //create consumer threads
    for ( ; ii < totalThreads; ii++)
    {
        pthread_create(&threads[ii], &attr, consumer, (void*)&thread_datas[ii]);
        thread_datas[ii].tid = threads[ii];
        thread_datas[ii].itemsMoved = 0;
        //printf("Created consumer thread %d\n", threads[ii]);
    }

    //sleep for simulationTime seconds
    sleep(simulationTime);

    //join all of the threads
    threadsRunning = false;
    for (int i = 0; i < totalThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    

    //display stats
    printf("\n\nPRODUCER / CONSUMER SIMULATION COMPLETE\n");
    printf("========================================\n");
    printf("Simulation Time:\t\t\t%d\n", simulationTime);
    printf("Maximum Thread Sleep Time:\t\t%d\n", maxThreadSleepTime);
    printf("Number of Producer Threads: \t\t%d\n", numProducers);
    printf("Number of Consumer Threads: \t\t%d\n", numProducers);
    printf("Size of Buffer: \t\t\t%d\n\n", BUFFER_SIZE);
    printf("Total Number of Items Produced: \t%d\n", itemsProduced);
    for (ii = 0; ii < numProducers; ii++)
    {
        printf("  Thread %ld: \t\t%d\n", thread_datas[ii].tid, thread_datas[ii].itemsMoved);
    }
    printf("\nTotal Number of Items Consumed: \t%d\n", itemsConsumed);
    for (; ii < totalThreads; ii++)
    {
        printf("  Thread %ld: \t\t%d\n", thread_datas[ii].tid, thread_datas[ii].itemsMoved);
    }
    

    return 0;
}

/**
 * producer
 *
 * This function alternates between waiting for a random number of seconds
 * under maxThreadSleepTime to sleep and attempting to add random numbers
 * to the buffer list
 *
 * void return value
 *
 * Value Parameters
 * ------------------
 * param        void*       this function needs its thread_data* instance passed 
 *
 */
void *producer(void *param)
{
    thread_data *thread_dat = (thread_data*)param;
    buffer_item randomNumber;
    while (threadsRunning)
    {
        sleep(rand()%maxThreadSleepTime);
        randomNumber = rand()%100;
        if (buffer_insert_item(randomNumber))
            printf("Producer %ld failed to insert a number", thread_dat->tid);
        else
        {
            thread_dat->itemsMoved++;
            itemsProduced++;
            if (outputBufSnapshots)
            {
                printf("Producer %ld writes %d\n", thread_dat->tid, randomNumber);
                printSnapshot();
            }
        }
            
    }
    pthread_exit(0);
}


/**
 * consumer 
 *
 * This function alternates between waiting for a random number of seconds
 * under maxThreadSleepTime to sleep and attempting to remove items from the 
 * buffer list
 * 
 *
 * void return value
 *
 * Value Parameters
 * ------------------
 * param        void*       this function needs its thread_data* instance passed 
 *
 */
void *consumer(void *param)
{
    thread_data *thread_dat = (thread_data*)param;
    buffer_item randomNumber;
    while (threadsRunning)
    {
        sleep(rand()%maxThreadSleepTime);
        if (buffer_remove_item(&randomNumber))
            printf("Consumer %ld failed to remove a number", thread_dat->tid);
        else
        {
            thread_dat->itemsMoved++;
            itemsConsumed++;
            if (outputBufSnapshots)
            {
                printf("Consumer %ld reads %d", thread_dat->tid, randomNumber);
                if (isPrime(randomNumber))
                {
                    printf(" * * * * Prime * * * *");
                }
                printf("\n");
                printSnapshot();
            }
                
        }
            
    }
    pthread_exit(0);
}


/**
 * buffer_insert_item
 * 
 * This function inserts an item into the buffer whenever
 * the mutex lock and semaphore full become available
 *
 *
 * Return Value
 * ------------------
 * bool                             false if successful
 *
 * Value Parameters
 * ------------------
 * item         buffer_item         item to insert
*/
bool buffer_insert_item( buffer_item item )
{
    int oldIn = in;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    //*********** CRITICAL SECTION **************
    buffers[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    if (buffers[oldIn] == 0)
        return true;
    else
        return false;
}


/**
 * buffer_remove_item
 * 
 * This function removes an item from the buffer whenever
 * the mutex lock and semaphore full become available
 *
 *
 * Return Value
 * ------------------
 * bool                             false if successful
 *
 * Value Parameters
 * ------------------
 * item         buffer_item*        place to store the removed item
*/
bool buffer_remove_item( buffer_item *item )
{
    
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    //*********** CRITICAL SECTION **************
    *item = buffers[out];
    buffers[out] = 0;
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    if (*item == 0)
        return true;
    else
        return false;
}


/**
 * printSnapshot
 *
 * This function prints a snapshot of the buffers in its current state
 */
void printSnapshot()
{
    int bufs = abs(in - out);
    printf("(buffers occupied: %d)\n", bufs);
    printf("buffers: ");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("\t%d", buffers[i]);
    }
    printf("\n\t");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("\t----");
    }
    printf("\n\t\t");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (i == in && i == out)
            printf(" RW\t");
        else if (i == in && !i == out)
            printf(" W\t");
        else if (i == out && !i == in)
            printf(" R\t");
        else
            printf("\t");
    }
    printf("\n");
}


bool isPrime(int number)
{

    if (number == 1 || number == 0)
    {
        return false;
    }

    for (int i = 2; i <= number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}


