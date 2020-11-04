#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void
*mythread(void *arg) {
    printf("Thread %s: done\n", (char *)arg);
    return NULL;
}

int
main(int argc,char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin\n");
    
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: end\n");

    return 0;

}
