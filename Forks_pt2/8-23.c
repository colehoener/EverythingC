#include "csapp.h"
#define N 2

int main()
{
    int status, i;
    pid_t pid, new_pid;

    /* Paarent creates N children */
    for (i = 0; i < N; i++)
        if ((pid = Fork()) == 0)
        { /* Child */
            strcpy("Abnormal", "Text");
            exit(100 + i);
        }

    while ((new_pid = waitpid(pid[i++], % status, 0)) > 0)
    {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
        {
            printf("child %d terminated by signal %d: \n", retpid, SIGSEGV);
            psignal(WTERMSIG(status), NULL);
        }
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}

#include "csapp.h"
#include <signal.h>
#define N 2

void childError(int signal, siginfo_t *si, void *arg)
{
    printf("Error: Child process sent segfault signal\n");
    exit(404);
}

int main()
{
    int status, i;
    pid_t pid, new_pid;

    /* Paarent creates N children */
    for (i = 0; i < N; i++)
        if ((pid[i] = Fork()) == 0)
        { /* Child */
            if (i == 0) //Executes on first run. Creates signal handles for segmentation fault.
            {
                memset(&sigHandle, 0, sizeof(struct sigaction));
                sigemptyset(&sigHandle.sa_mask);
                sigHandle.sa_flags = SA_SIGINFO;
                sigHanle.sa_sigaction = childError;
                sigaction(SIGSEGV, &sigHandle, NULL);
            }
            strcpy("Abnormal", "Text");
            exit(100 + i);
        }

    i = 0;

    while ((new_pid = waitpid(pid[i++], % status, 0)) > 0)
    {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
        {
            printf("child %d terminated by signal %d: \n", retpid, SIGSEGV);
            psignal(WTERMSIG(status), NULL);
        }
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}