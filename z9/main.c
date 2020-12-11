#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        printf("Wrong way of usage function\n");
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
        execl("/bin/cat", "cat", argv[1], NULL);
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
                printf("cp is signalled by %d\n", WTERMSIG(status));
            }
            else if (WIFSTOPPED(status))
            {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            }
            else if (WIFCONTINUED(status))
            {
                printf("continued after stop or smth else\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    printf("i'm here\n");
    return 1;
}

