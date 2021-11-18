#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int SharedVariable = 0;


void SimpleThread(int which) {
    int num, val;
    for(num = 0; num < 20; num++) {
        if (rand() > RAND_MAX / 2)
            usleep(10);

        val = SharedVariable;
        printf("*** thread %d sees value %d\n", which, val);
        SharedVariable = val + 1;
    }
    val = SharedVariable;
    printf("Thread %d sees final value %d\n", which, val);

    pthread_exit(0);
}


int main(int argc, char **argv)
{

    if(argc < 3)
    {
        int number;

        sscanf(argv[1], "%d", &number); // Using sscanf
        printf("\nThe value of x : %d", number);

        for(int i = 1; i < number + 1; i++)
        {
            pthread_t tid;

            pthread_attr_t attr;

            pthread_attr_init(&attr);

            pthread_create(&tid, &attr, SimpleThread, i);

            pthread_join(tid, NULL);
        }
        
    }


}