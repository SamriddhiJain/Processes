///error in this approach

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void printPrimes(int x){
  return;
}

void printFib(int x){
  return;
}

void printCommon(int x){
  return;
}

int child(int t,int x){
  
  pid_t p1=fork();
  pid_t p2=fork();

  if(p1==-1 || p2==-1){
        printf("Error in forking in child%d\n",x);
        return;
  }

  if(p1==0){
        grandchild(t,x,1);
        return;
  }else if(p2==0){
        grandchild(t,x,2);
        return;
  }else{
        printf("This is child%d\n",x);
        printPrimes(t);
        return;
  }

  return;
}

int grandchild(int t,int x,int y){
  pid_t p1=fork();
  pid_t p2=fork();

  if(p1==-1 || p2==-1){
        printf("Error in forking in child%d\n",x);
        return;
  }

  if(p1==0){
        greatgrandchild(t,x,y,1);
        return;
  }else if(p2==0){
        greatgrandchild(t,x,y,2);
        return;
  }else{
        printf("This is grandchild%d from child%d\n",y,x);
        printFib(t);
        return;
  }

  return;
}

int greatgrandchild(int t,int x,int y,int z){
  printf("This is greatgrandchild%d from grandchild%d from child%d\n",z,y,x);
  printCommon(t);

  return;
}

int main(){

  int n,i;
  scanf("%d",&n);

  pid_t child1=fork();
  pid_t child2=fork();
  
  if(child1==-1 || child2==-1){
        printf("Error in forking\n");
        return;
  }

  if(child1==0){
        //child(n,1);
        printf("dsvsf\n");
        return;
  }else if(child2==0){
        printf("wvve\n");
        //child(n,2);
        return;
  }else{
        printf("This is still the parent\n");
        return;
  }
  wait();
  return 0;
}