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

    pthread_exit(NULL);

}

//Checks if argument is a positive number
int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        return 0;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}


int main(int argc, char **argv)
{

    if(argc < 3)
    {
        

        if(isNumber(argv[1]) )
        {
            int number;

            sscanf(argv[1], "%d", &number); // Using sscanf to turn the char into an int


            //Generating multiple threads
            pthread_t tid[number];
            for(int i = 0; i < number; i++)
            {
                tid[i] = i;
            }

            //Creating multiple threads
            for(int i = 1; i < number + 1; i++)
            {
                pthread_attr_t attr;

                pthread_attr_init(&attr);

                pthread_create(&tid[i - 1], &attr, SimpleThread, i);
            }

            for(int i = 0; i < number; i++)
            {
                pthread_join(tid[i], NULL);
            }
        }
        else{
            printf("Invalid Input");
        }


        
    }


}