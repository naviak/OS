#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <memory.h>
#define BUFFER_SIZE 256
void close_pipe(FILE *pipe)
{
    int status = pclose(pipe);
    if (status == -1)
    {
        perror("pclose");
        exit(0);
    }
    else if (WEXITSTATUS(status) != 0)
    {
        perror("child process returned bad exit status");
    }
    else if (WIFSIGNALED(status) != 0)
    {
        perror("child process interrupted by signal");
    }
}

int main(int argc, char *argv[])
{
    FILE *pipe = popen("grep ^$ text.txt | wc -l ", "r");
    if (pipe == NULL)
    {
        perror("popen");
        return 0;
    }
    char buf[BUFFER_SIZE];
    char*  str_number = fgets(buf, BUFFER_SIZE, pipe);
    if(str_number == NULL && !feof(pipe))
    {
        perror("fgets");
        return 0;
    }
    close_pipe(pipe);
    char* end_ptr;
    printf("There is %u  blank lines\n", (unsigned)strtol(str_number, &end_ptr, 10));
    return 1;
}

