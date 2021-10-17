#include "csapp.h"
void *thread(void *vargp);

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, thread, NULL);
    pthread_exit(NULL);
}

void *thread(void *vargp){
    sleep(1);
    printf("Hello, world!\n");
    return NULL;
}