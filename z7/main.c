#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define filename "text.txt"

typedef struct Table
{
    size_t offset;
    size_t length;
} Table;


int fillTable(Table *table, int filesize, char *buf);
void readLine(Table *table, int number, char* buf);


int main()
{
    int file = open(filename, O_RDONLY);
    if (file == -1)
    {
	printf("Cannot open file\n");
	return 0;
    }
    int filesize = lseek(file, 0, SEEK_END);
    if (filesize == -1)
    {
	close(file);
        return 0;
    }
    lseek(file, 0, SEEK_SET);
    Table table[filesize];
    memset(table, 0, filesize * sizeof(Table));
    char* mapf;
    if ((mapf = mmap(0,filesize,PROT_READ,MAP_SHARED,file,0)) == MAP_FAILED)
    {
	printf("Mmap error\n");
        close(file);
        return 0;
    }
    printf("\n");
    for(int i = 1; i < filesize; ++i)
    {
   	 printf("%c",mapf[i]);
    }
    printf("\n");
    int lineCount = fillTable(table, filesize, mapf);
    printf("You have 5 seconds to put number of line\n");
    fd_set rfds;
    struct timeval tv;
    int retval;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    retval = select(1, &rfds, NULL, NULL, &tv);
    if(retval)
    {
	while(1)
	{
	    int lineNumber;
	    scanf("%d", &lineNumber);
            if (lineNumber == -1) { break; }
            if ( lineNumber < 1 || lineNumber >= lineCount) { printf("This line doenst exist \n"); } 
	    else { readLine(table, lineNumber, mapf); }
        }
    }
    else{ printf("Your time is left\n");}
    close(file);
    return 1;
}


int fillTable(Table *table, int filesize, char *buf)
{
    int lineCount = 0;
    for (int i = 0; i < filesize; ++i)
    {
        if (buf[i] != '\n')
	{
            table[lineCount].length++;
        }
	else
	{
            ++lineCount;
            table[lineCount].offset = table[lineCount - 1].offset + table[lineCount - 1].length + 1;
        }
    }
    return lineCount;
}

void readLine(Table *table, int number, char* buf)
{
    for (int i = 0; i < table[number].length; ++i)
    {
        printf("%c", buf[table[number].offset + i]);
    }
    printf("\n");
}
