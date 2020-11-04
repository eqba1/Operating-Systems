#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;
static volatile int counter = 0;

// mythread()
//
// Simple adds 1 to counter repeatedly, in a loop
// Yes, this is add 10,000,000 to a counter
// and show the solve problem nicely

void
*mythread(void *arg) {

    pthread_mutex_lock(&lock);

    printf("%s: begin\n", (char *) arg);
    int i;
    for ( i = 0; i < 1e7; i++ ) {
        counter = counter +1;
    }
    printf("%s: done\n", (char *) arg);

    pthread_mutex_unlock(&lock);

    return NULL;
}

// main()
//
// launches two threads (pthread_create)
// and then waits for them (pthread_join)
int 
main (int argc, char *argv[]) {
    pthread_t p1, p2;

    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex init FAILED\n");
        return 1;
    }

    printf("main: begin (counter = %d)\n", counter);
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: done with both (counter = %d)\n",
            counter);
    return 0;
}
