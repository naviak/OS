#include <sys/types.h>
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


int fillTable(Table *table, int filesize, char *buffer);
void readLine(Table *table, int number, char* buffer);


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
    char buffer[filesize];
    if (read(file, buffer, filesize) == -1)
    {
	close(file);
        return 0;
    }
    printf("\n");
    for(int i = 1; i < filesize; ++i)
    {
   	 printf("%c",buffer[i]);
    }
    printf("\n");
    int lineCount = fillTable(table, filesize, buffer);
    if (lineCount > 0)
    {
        int lineNumber;
        while (scanf("%d", &lineNumber))
	{
            if (lineNumber == -1) { break; }
            if ( lineNumber < 1 || lineNumber >= lineCount) { printf("This line doenst exist \n"); } 
	    else { readLine(table, lineNumber, buffer); }
        }

    }
    else if (lineCount == 0)
    {
	 return 0;
    }
    close(file);
    return 1;
}


int fillTable(Table *table, int filesize, char *buffer)
{
    int lineCount = 0;
    for (int i = 0; i < filesize; ++i)
    {
        if (buffer[i] != '\n')
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

void readLine(Table *table, int number, char* buffer)
{
    for (int i = 0; i < table[number].length; ++i)
    {
        printf("%c", buffer[table[number].offset + i]);
    }
    printf("\n");
}
