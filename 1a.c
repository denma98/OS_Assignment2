#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define bill 1e9
struct timespec Tstp1a, Tstp1b, Tstp2a, Tstp2b, Tstp3a, Tstp3b;
pthread_t thread1, thread2, thread3;
struct sched_param param1, param2, param3;

void *ThrA(void *asd)
{
    pthread_setschedparam(thread1, SCHED_OTHER, &param1);
    long int num = 0;
    clock_gettime(CLOCK_BOOTTIME, &Tstp1a);
    float initial1 = Tstp1a.tv_sec;

    for (long int i = 1; i < pow(2, 32); i++)
    {
        num++;
    }
    clock_gettime(CLOCK_BOOTTIME, &Tstp1b);
    float initial2 = Tstp1b.tv_sec;

    printf("The clock time needed was: %lf seconds\n", (initial2 - initial1) + ((Tstp1b.tv_nsec - Tstp1a.tv_nsec) / bill));
    pthread_exit(NULL);
}

void *ThrB(void *sad)
{
    pthread_setschedparam(thread2, SCHED_RR, &param2);

    long int num = 0;
    clock_gettime(CLOCK_BOOTTIME, &Tstp2a);
    float initial1 = Tstp2a.tv_sec;

    for (long int i = 1; i < pow(2, 32); i++)
    {
        num++;
    }
    clock_gettime(CLOCK_BOOTTIME, &Tstp2b);
    float initial2 = Tstp2b.tv_sec;

    printf("The clock time needed was: %f seconds\n", ((initial2 - initial1) + (Tstp2b.tv_nsec - Tstp2a.tv_nsec) / bill));
    pthread_exit(NULL);
}

void *ThrC(void *asd)
{
    pthread_setschedparam(thread1, SCHED_FIFO, &param3);

    long int num = 0;
    clock_gettime(CLOCK_REALTIME, &Tstp3a);
    float initial1 = Tstp2a.tv_sec;

    for (long int i = 0; i < pow(2, 32); i++)
    {
        num++;
    }
    clock_gettime(CLOCK_REALTIME, &Tstp3b);
    float initial2 = Tstp2b.tv_sec;

    printf("The clock time needed was: %f seconds\n", ((initial2 - initial1) + (Tstp3b.tv_nsec - Tstp3a.tv_nsec) / bill));
    // pthread_exit(NULL);
}

int main()
{

    // sched-other thr-b thr-c
    pthread_attr_t att1, att2, att3;

    pthread_attr_init(&att1);
    pthread_attr_init(&att3);
    pthread_attr_init(&att2);

    param1.sched_priority = 0;
    param2.sched_priority = 20;
    param3.sched_priority = 90;

    if (pthread_create(&thread1, &att1, &ThrA, NULL) != 0)
    {

        return 0;
    }

    // second

    if (pthread_create(&thread2, &att2, &ThrB, NULL) != 0)
    {

        return 0;
    }

    // third

    if (pthread_create(&thread3, &att3, &ThrC, NULL) != 0)
    {
        return 0;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}