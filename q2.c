#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void child1(){
  printf("Child starts where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
  sleep(20);
  printf("Child ends where pid=%d and parent id= %d\n",(int)getpid(),(int)getppid());
}

void parent(){
  printf("Parent starts where pid=%d\n",(int)getpid());
  sleep(10);
  wait();
  printf("Parent ends where pid=%d\n",(int)getpid());
}

int main(int argc, char* argv[]){
  pid_t newid1=fork();
  
  if(newid1==-1){
        printf("Error in forking\n");
        return;
  }else if(newid1==0){
        child1();
        //execv("sleep",argv);
        return;
  }else{
        parent();
        return;
  }

  return 0;
}