#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{	
	FILE * f_pid;
	char str[40];

	f_pid=fopen("./shared_pid.txt","wr");

	printf("hello I am %d \n",getpid());
	fprintf(f_pid,"%d\n",getpid());
	fclose(f_pid);	
	scanf("%s",&str);

	return 0;
}
