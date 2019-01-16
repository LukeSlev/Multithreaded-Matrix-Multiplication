#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


#include "lab1_IO.h"
#include "timer.h"

int   thread_count;
int** A;
int** B;
int** C;
int n;

void* threadfunc(void* rank) {
  long my_rank = (long) rank;
  int i, j, k;
  int x = floor(my_rank/sqrt(thread_count));
  int y = my_rank % (int)sqrt(thread_count);

  int my_first_row = (n*x)/(int)sqrt((double)thread_count);
  int my_last_row = (n*(x+1))/(int)sqrt((double)thread_count);

  int my_first_col = (n*y)/(int)sqrt(thread_count);
  int my_last_col = (n*(y+1))/(int)sqrt(thread_count);

  printf("rank:%li x:%i y:%i\n",my_rank,x,y);
  printf("Yo fr:%i lr:%i fc:%i lc:%i\n",my_first_row,my_last_row,my_first_col,my_last_row);
  for (i = my_first_row; i < my_last_row; i++) {
    for (j = my_first_col; j < my_last_col; j++) {
      printf("i:%i j:%i\n",i,j);
      int sum = 0;
      for (k = 0; k < n; k++) {
        printf("C:%i A:%i * B:%i | i:%i j:%i k:%i\n",C[i][j],A[i][k],B[k][j],i,j,k);
        sum += A[i][k]*B[k][j];
      }
      C[i][j] = sum;
    }
  }printf("done\n");

  return NULL;
}


/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  double     start, end;
  long       thread, thread2;
  pthread_t* thread_handles;
  int        i;

  if (argc != 2) {
    printf("Wrong number of args dude");
    exit(1);
  }
  thread_count = atoi(argv[1]);
  if (sqrt(thread_count)*sqrt(thread_count) != thread_count) {
    printf("Thread count not a square number!!");
    exit(1);
    // Usage(argv[0]);
  }

  thread_handles = malloc(thread_count*sizeof(pthread_t));


  Lab1_loadinput(&A, &B, &n);

  C = malloc(n * sizeof(int*));

  for (i = 0; i < n; i++)
  {
    C[i] = malloc(n * sizeof(int));
  }
  // Check if n**2 is divisible by thread_count
  if ( (int)(n*n)% thread_count != 0) {
    printf("N*N not divisible by thread_count dummy");
    exit(1);
  }

  GET_TIME(start);
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL,
        threadfunc, (void*) thread);

  for (thread2 = 0; thread2 < thread_count; thread2++)
    pthread_join(thread_handles[thread2], NULL);
  GET_TIME(end);

  Lab1_saveoutput(C, &n, end-start);


  free(A);
  free(B);
  free(C);

  return 0;
}  /* main */
