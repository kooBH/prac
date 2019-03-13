#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
	FILE *fp;
    char cmd[100];
	char tmp[100];
	int pid;
	int found_flag = 0;
	//printf("stat : %d\n",system("gnome-terminal -x 'bash' -c  './p'  "));
 	

	fp = popen("ps -a", "r");
	/*
	 * PID		TTY		TIME		CMD
	 * 3775		pts/2	00:00:00	ps
	 * 3695     pts/2   00:00:00    record
	 * ...
	 * need to get PID of CMD 'record'
	 */	
	//First line
	fscanf(fp,"%s%s%s%s",tmp,tmp,tmp,tmp);
	while( (fscanf(fp,"%d%s%s%s",&pid,tmp,tmp,cmd) != EOF) && !found_flag )
	{
//		printf("%s : %d\n",cmd,pid);
		if(!strcmp(cmd,"record"))
		{
			printf("PID of process 'record' is %d\n",pid);
			found_flag =1;
		}
	}
	if(!found_flag)
		system("gnome-terminal -x 'bash'  -c  './p'")
	

	fclose(fp);
	return 0;

}
