#include <pthread.h>
#include "csapp.h"
#define NUMTHRDS 4
#define VECLEN 100000
pthread_t callThd[NUMTHRDS];
double *array_a;
double *array_b;
double big_sum;
int veclen;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct threadArg
{
    int threadNum;
};

void *dotprod(void *arg)
{
    double *x;
    double *y;
    double mysum;
    struct threadArg * argument;
    argument = (struct threadArg *) arg;
    int i;
    int start = argument -> threadNum;
    int end = start + 1;
    
    x = array_a;
    y = array_b;
    /* ... */
    
    mysum = 0;
    for (i = start; i < end; i++)
    {
        mysum += (x[i] * y[i]);
    }
    /* ... */
    pthread_mutex_lock( &mutex );
    big_sum += mysum;
    pthread_mutex_unlock( &mutex ) ;  
    pthread_exit(0);
    /* ... */
}

int main(int argc, char *argv[])
{
    long i;
    double *a, *b;
    void *status;
    a = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));
    b = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));
    for (i = 0; i < VECLEN * NUMTHRDS; i++)
    {
        a[i] = 1;
        b[i] = a[i];
    }
    veclen = VECLEN;
    array_a = a;
    array_b = b;
    big_sum = 0;
    /* ... */
    
    struct threadArg * tA1;
    tA1 = (struct threadArg *) calloc (1, sizeof(struct threadArg));
 
    /* ... */
    for (i = 0; i < NUMTHRDS; i++)
    {
        tA1 -> threadNum = i;
        Pthread_create(&callThd[i], NULL, dotprod, (void * ) tA1);
        pthread_join ( callThd[i] ,&status ) ;
    }
    
    printf("Sum = %f \n", big_sum);
    free(a);
    free(b);
    pthread_mutex_destroy ( &mutex ) ;
    pthread_exit ( NULL ) ;
}