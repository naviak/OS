#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
bool openfile(const char* filename)
{
	FILE* file = fopen(filename, "r" );
	if(file!= NULL)
	{
		printf("FILE IS OPENED SUCCESSFULLY\n");
		fclose(file);
		return true;
	}
	else
	{
		perror("CANNOT OPEN FILE");
		return false;
	}
}
int main()
{
	printf("Real User ID = %d\n", getuid());
	printf("Effective User ID = %d\n", geteuid());
	const char* filename = "test.txt";
	int res = openfile(filename);
	if(res)
	{
		setuid(getuid());
		printf("Real User ID = %d\n", getuid());
		printf("Effective User ID = %d\n", geteuid());
	        openfile(filename);
	}
	return 0;
}

