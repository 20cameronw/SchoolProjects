/**
 * Cameron Weston
 * CSC 360 
 * Project 3a: Timing multithreaded compute_pi function
 * 9/18/2022
*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_THREADS 512

void *compute_pi(void *);

long sample_points;
long total_hits;
long total_misses;
long hits[MAX_THREADS];
long sample_points_per_thread;
int num_threads;

int main(int argc, char *argv[])
{
  /* local variables */
  int ii;
  int retval;
  pthread_t p_threads[MAX_THREADS];
  pthread_attr_t attr;
  double computed_pi;

  //timer variables
  struct timeval start, end;
  long mtime, seconds, useconds;

  /* initialize local variables */
  retval = 0;

  //record the time at start
  gettimeofday(&start, NULL);

  //init attributes with default params
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  /* parse command line arguments into sample points and number of threads */
  /* there is no error checking here!!!!! */
  sample_points = atol(argv[1]);
  num_threads = atoi(argv[2]);

  total_hits = 0;
  sample_points_per_thread = sample_points / num_threads;

  for (ii = 0; ii < num_threads; ii++)
  {
    hits[ii] = ii;
    pthread_create(&p_threads[ii], &attr, compute_pi, (void *)&hits[ii]);
  }

  for (ii = 0; ii < num_threads; ii++)
  {
    pthread_join(p_threads[ii], NULL);
    total_hits += hits[ii];
  }

  computed_pi = 4.0 * (double)total_hits / ((double)(sample_points));

  //record the time after computing
  gettimeofday(&end, NULL); 

  printf("Computed PI = %lf\n", computed_pi);
  
  //calculate the elapsed time
  seconds = end.tv_sec - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  mtime = ((seconds)*1000 + useconds / 1000.0) + 0.5;
  printf("Elapsed time: %ld milliseconds\n", mtime);

  /* return to calling environment */
  return (retval);
}

void *compute_pi(void *s)
{
  int seed;
  long ii;
  long *hit_pointer;
  long local_hits;
  double rand_no_x;
  double rand_no_y;

  hit_pointer = (long *)s;
  seed = *hit_pointer;
  local_hits = 0;

  for (ii = 0; ii < sample_points_per_thread; ii++)
  {
    rand_no_x = (double)(rand_r(&seed)) / (double)RAND_MAX;
    rand_no_y = (double)(rand_r(&seed)) / (double)RAND_MAX;
    if (((rand_no_x - 0.5) * (rand_no_x - 0.5) +
         (rand_no_y - 0.5) * (rand_no_y - 0.5)) <= 0.25)
      local_hits++;
    seed *= ii;
  }

  *hit_pointer = local_hits;
  pthread_exit(0);
}