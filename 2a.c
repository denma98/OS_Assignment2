#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#define bill 1e9
int main()
{

    pid_t pid1;

    pid1 = fork();

    if (pid1 == 0)
    {
        struct timespec Tstp1a, Tstp1b;

        clock.gettime(CLOCK_REALTIME, &Tstp1a);

        printf(" child 1 -> process id = %d  and parent process id = %d\n", getpid(), getppid());
        char s[50] = "chrt -r -p ";
        char p[30];

        sprintf(p, % d, getpid());
        strcat(s, p);

        system(s);
        ///------------------
        char s1[50] = "chrt -p ";
        char p1[30];

        sprintf(p1, % d, getpid());
        strcat(s1, p1);

        system(s1);

        char **arg = {NULL};
        execvp("./shell.sh", arg);
        clock.gettime(CLOCK_REALTIME, &Tstp1b);
        float initial1 = Tstp1a.tv_sec;
        float initial2 = Tstp1b.tv_sec;

        printf("The clock time needed was: %lf seconds\n", ((initial2 - initial1) + (Tstp1b.tv_nsec - Tstp1a.tv_nsec) / bill));
    }

    else
    {

        pid_t pid2;
        pid2 = fork();

        if (pid2 == 0)
        {
            struct timespec Tstp1a, Tstp1b;

            clock.gettime(CLOCK_REALTIME, &Tstp1a);
            printf(" child 2 -> process id = %d and parent process id = %id\n", getpid(), getppid());

            char s[50] = "chrt -r -p 4 ";
            char p[30];

            sprintf(p, % d, getpid());
            strcat(s, p);

            system(s);

            char s1[50] = "chrt -p ";
            char p1[30];

            sprintf(p1, % d, getpid());
            strcat(s1, p1);

            system(s1);

            char **arg = {NULL};
            execvp("./shell.sh", arg);

            clock.gettime(CLOCK_REALTIME, &Tstp1b);
            float initial1 = Tstp1a.tv_sec;
            float initial2 = Tstp1b.tv_sec;

            printf("The clock time needed was: %lf seconds\n", ((initial2 - initial1) + (Tstp1b.tv_nsec - Tstp1a.tv_nsec) / bill));
        }

        else
        {

            pid_t pid3;
            pid3 = fork();

            if (pid3 == 0)
            {
                struct timespec Tstp1a, Tstp1b;

                clock.gettime(CLOCK_REALTIME, &Tstp1a);
                printf(" child 3 -> process id = %d and parent process id = %id\n", getpid(), getppid());

                char s[50] = "chrt -r -p ";
                char p[30];

                sprintf(p, % d, getpid());
                strcat(s, p);

                system(s);
                char s1[50] = "chrt -p ";
                char p1[30];

                sprintf(p1, % d, getpid());
                strcat(s1, p1);

                system(s1);

                char **arg = {NULL};
                execvp("./shell.sh", arg);
                clock.gettime(CLOCK_REALTIME, &Tstp1b);
                float initial1 = Tstp1a.tv_sec;
                float initial2 = Tstp1b.tv_sec;

                printf("The clock time needed was: %lf seconds\n", ((initial2 - initial1) + (Tstp1b.tv_nsec - Tstp1a.tv_nsec) / bill));
            }

            else
            {
                while (wait(NULL) > 0)
                {
                }

                printf(" parent -> process id: %d\n", getpid());
                // clock.gettime(CLOCK_REALTIME)
            }
        }
    }

    return 0;
}