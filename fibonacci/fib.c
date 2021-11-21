#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0;
int current = 1;
int previous = 0;
void *runner(void *param);

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
    pthread_t tid;
    pthread_attr_t attr;

    if (argc != 2){
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }

    int number;
    sscanf(argv[1], "%d", &number); // Using sscanf to get the number

    if (isNumber(argv[1]) == 0){
        printf("Invalid Number\n");
        return -1;
    }

    //Creating threads
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, runner, argv[1]);

    pthread_join(tid, NULL);


    printf("sum = %d\n", sum);

    

}

void *runner(void *param)
{
    int i, upper = atoi(param);

    //fibonacci
    for (i = 1; i < upper; i++)
    {
        sum = current + previous;
        previous = current;
        current = sum;

    }

    pthread_exit(0);
}

