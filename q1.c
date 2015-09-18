#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

void child1(){
  FILE *fp1=fopen("test.txt","w");
  int i=1000;

  while(i>0){
        fprintf(fp1,"%d\n",i--);
  }

  sleep(100);

  fclose(fp1);
}

void childHog(){
  while(1){
        //do nothing 
  }
}

void childSleep(int x){
  sleep(x);
}

int main(){
  pid_t newid1=fork();
  setpriority(PRIO_PROCESS, PRIO_PGRP, 0);

  if(newid1==-1){
        printf("Error in forking\n");
        return;
  }else if(newid1==0){

        setpriority(PRIO_PROCESS, PRIO_PGRP, -2);
        printf("This is Job1 where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
        child1();
        return;
  }else{

        pid_t newid2=fork();

        if(newid2==0){
              setpriority(PRIO_PROCESS, PRIO_PGRP, -15);
              printf("This is Job2 where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
              childHog();
              return;
        }else{

              pid_t newid3=fork();

              if(newid3==0){
                    setpriority(PRIO_PROCESS, PRIO_PGRP, 15);
                    printf("This is Job3 where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
                    childHog();
                    return;
              }else{

                    pid_t newid4=fork();

                    if(newid4==0){
                          setpriority(PRIO_PROCESS, PRIO_PGRP, -20);
                          printf("This is Job4 where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
                          childSleep(100);
                          return;
                    }else{
                          wait();
                          return;
                    }
              }
        }       
  }

  wait();
  return 0;
}