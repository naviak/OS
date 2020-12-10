#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        printf("Wrong way of usage function\n", argv[0]);
        return 0;
    }
    int status;
    pid_t cpid;
    cpid = fork();
    if (cpid == -1)
    {
        perror("fork() error: ");
        return 0;
    }
    if(cpid == 0)
    {
        execvp(argv[1], &argv[1]);
        return 1;
    }
    else
    {
        do
        {
            pid_t w = waitpid(cpid, &status, 0);
            if (w == -1)
            {
                perror("smth wrong w/ child process ");
                return 0;
            }
             if (WIFSIGNALED(status))
            {
                printf("cp killed by signal %d\t cp: %d\n", WTERMSIG(status), cpid);
            }
            else if (WIFSTOPPED(status))
            {
                printf("stopped by signal %d\t cp: %d\n", WSTOPSIG(status), cpid);
            }
            else if (WIFCONTINUED(status))
            {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    printf("i'm here\n");
    return 1;
}

