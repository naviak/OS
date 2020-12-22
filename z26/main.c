#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 256

void close_pipe(FILE* pipe)
{
    int status = pclose(pipe);
    if (status == -1)
    {
        printf("error during pclose\n");
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    FILE* pipe = popen("echo i'm here", "r");
    if (pipe == NULL)
    {
        perror("popen");
        return 0;
    }

    char buf[BUFFER_SIZE];
    size_t read_count = fread(buf, sizeof(char), BUFFER_SIZE, pipe);
    if (ferror(pipe) == -1)
    {
        close_pipe(pipe);
        return 0;
    }
    close_pipe(pipe);
    size_t i;
    for (i = 0; i < read_count; i++)
    {
        buf[i] = (char)toupper(buf[i]);
    }
    size_t written_count = fwrite(buf, read_count, sizeof(char), stdout);
    if (ferror(pipe) == -1)
    {
        return 0;
    }
    return 1;
}
