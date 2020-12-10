#include <stdio.h>
#include <signal.h>
#include <termio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

static struct termios savetty;

void sigcatch(int n) {
    tcsetattr(STDIN_FILENO, TCSANOW, &savetty);
    exit(-1);
}

int main()
{
    struct termios newtty;
    signal(SIGINT, sigcatch);
    if (tcgetattr(STDIN_FILENO, &savetty) == -1)
    {
        printf("tcgetattr failed: no terminal\n");
        return 0;
    }
    newtty = savetty;
    newtty.c_lflag &= ~ICANON;
    newtty.c_lflag &= ~ECHO;
    newtty.c_cc[VMIN] = 1;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newtty) == -1)
    {
        fprintf(stderr, "Can not switch the terminal mode\n");
        return 0;
    }
    printf("([Y] for Yes\t [N] for No ?\n");
    while (1)
    {
        char buf;
        if (read(STDIN_FILENO, &buf, 1) == 1)
        {
            if (tolower(buf) == 'y')
            {
                printf("You chose: Yes\n");
                tcsetattr(STDIN_FILENO, TCSANOW, &savetty);
                break;
            }
            else if (tolower(buf) == 'n')
            {
                printf("You chose: No\n");
                tcsetattr(STDIN_FILENO, TCSANOW, &savetty);
                break;
            }
            else
            {
                write(STDOUT_FILENO, "\a", 1);
            }
        }
        else
        {
            fprintf(stderr, "Couldn't read from standard input");
        }
    }
    return 1;
}
