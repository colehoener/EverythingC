#include "csapp.h"

void *thread(void *vargp);

int main(int argc, char **argv)
{
    int n;
    int i = 0;
    

    //Argument checking
    if (argc < 2)
    {
        printf("Not enough arguments. Program terminated.\n");
        exit(0);
    }
    else if(argc > 2)
    {
        printf("Too many arguments. Program terminated.\n");
        exit(0);
    }

    n = atoi(argv[1]);
    pthread_t tid[n];

    //Create n threads
    for(i = 0; i < n; i++){
        Pthread_create(&tid[i], NULL, thread, NULL);
        Pthread_join(tid[i], NULL);
    }
    
    exit(0);
}

void *thread(void *Vargp) /* Thread routine */
{
    printf("Hello, world!\n");
    return NULL;
}