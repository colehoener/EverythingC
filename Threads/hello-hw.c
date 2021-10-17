#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NUM_THREADS 8
char *messages[NUM_THREADS];

struct threadArg
{
    int taskNum;
    char message[8];
    int summation;
};

void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;

    //Creat struct for argument and get values from argument
    struct threadArg * argument;
    argument = (struct threadArg *) threadarg;
    taskid = argument -> taskNum;
    hello_msg = argument -> message;
    sum = argument -> summation;

    printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    //Declare struct
    struct threadArg * tA1;
    pthread_t threads[NUM_THREADS];

    int rc, t, sum;
    sum = 0;
    messages[0] = "Hello-0";
    messages[1] = "Hello-1";
    messages[2] = "Hello-2";
    messages[3] = "Hello-3";
    messages[4] = "Hello-4";
    messages[5] = "Hello-5";
    messages[6] = "Hello-6";
    messages[7] = "Hello-7";

    //Create instance of struct
    tA1 = (struct threadArg *) calloc (1, sizeof(struct threadArg));
    
    for (t = 0; t < NUM_THREADS; t++)
    {
        sum = sum + t;

        //Assign the correct values to the struct
        tA1 -> taskNum = t;
        strcpy(tA1 -> message, messages[t]);
        tA1 -> summation = sum;

        printf("Creating thread %d\n", t);

        //Create thread and join so they finish efore another is run
        pthread_create(&threads[t], NULL, PrintHello, (void * ) tA1);
        pthread_join(threads[t], NULL);
    }
    pthread_exit(NULL);
}