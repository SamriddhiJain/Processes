#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
int main (void)
{
    pid_t pid1,pid2;
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
    char buffer[800];
    long double loadavg;
    char  string1[] = "Hello, child process 1\n";
    char  string2[] = "Hello, child process 2\n";
    char  string3[] = "Hello Parent process, its child process 1\n";
    char  string4[] = "Hello Parent process, its child process 2\n";

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    pid1= fork();
    pid2= fork();

    if(pid1 == -1)
        {
           perror("fork");
           exit(1);
       }
    if(pid2 == -1)
        {
           perror("fork");
           exit(1);
        }
    if (pid1 ==0) 
    {
          close(pipe1[1]);     /*pipe1 will be used for getting input to child process 1*/
          close(pipe2[0]);     /*pipe2 will be used for giving output to parent process*/
          write(pipe2[1], string3 , (strlen(string3)+1));
          read(pipe1[0], buffer, sizeof(buffer));
          printf("Received string from parent to child process 1: %s", buffer);
    }
    else if(pid2 ==0)
    {
        close(pipe3[1]);        /*pipe3 will be used for getting input for child process 2*/
        close(pipe4[0]);                           /*pipe4 will be used for giving output to parent process*/
        long double a[4], b[4], loadavg;
        FILE *fp;
        char dump[50];

        for(;;)
        {
        fp = fopen("../../../../../proc/stat","r");
        if(!fp) {
		printf("No file Exists!!\n");
		return 1;
	}
        fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
        fclose(fp);
        sleep(1);

        fp = fopen("../../../../proc/stat","r");
        fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
        fclose(fp);

        loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
        write(pipe4[1], &loadavg, sizeof(loadavg));
        read(pipe3[0], buffer, sizeof(buffer));
        printf("Received string from parent to child process 2: %s", buffer);
        }
    }
    else
      {
         close(pipe1[0]);       /*pipe1 will be used to give input to child process 1*/
         close(pipe2[1]);       /*pipe2 is used to get output from child process 1*/
         close(pipe3[0]);       /*pipe3 will be used to give input to child process 2*/
         close(pipe4[1]);       /*pipe4 is used to get output from child process 2*/
         write(pipe1[1], string1 , (strlen(string1)+1));
         write(pipe3[1], string2 , (strlen(string1)+1));
         read(pipe2[0], buffer, sizeof(buffer));
         printf("Received string from child process 1 to parent: %s", buffer);
         read(pipe4[0], buffer, sizeof(buffer));
         printf("Received string  from child process 2 to parent: %s", buffer);
       
      }
}
