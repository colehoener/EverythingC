#include <stdio.h>
#include <pthread.h>

struct data_t
{
    double procVal;
    int id;
    int thisCount;
};

int count;

void *work (void * arg)  {
    struct data_t * someData;
    char buffer[128];

    //So if i read the instructions correctly, you have to read 128 bytes at a time so thats what
    //this does. But if the instructions actually meant to read 1 byte at a time up to 128 the code
    //would look slightly different. I would ask for clarfication but unfortuntley im not in a 
    //classroom right now.
    while(fread(&buffer, sizeof(buffer), 128, arg) == 128){
         count++;
        someData -> procVal = proc(buffer);
        someData -> id = pthread_self();
        someData -> thisCount = count;

        enque(someData);
    }  
}

int main(int argc, char *argv[])
{
    count = 0;
    //initque();

    FILE *f1;
    FILE *f2;

    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[1], "r");

    pthread_t threads[2];
    
    pthread_create(&threads[0], NULL, work, (void * ) f1);
    pthread_join(threads[0], NULL);
    
    pthread_create(&threads[1], NULL, work, (void * ) f2);
    pthread_join(threads[1], NULL);

    fclose(f1);
    fclose(f2);

    printf("%d", count);
    exit(0);
}