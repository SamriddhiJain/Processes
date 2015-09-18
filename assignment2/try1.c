#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t  pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)                      //child process
{  
    sleep(18);                  
    printf("Its child process: %d\n", (int)getppid());
    
}

void  ParentProcess(void)
{
     sleep(9);
     wait();                                //wait function 
     printf("its parent process: %d\n", (int)getpid());
}
