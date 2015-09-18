#include  <stdio.h>
#include  <sys/types.h>
          
void ChildProcess1(int no);
void ChildProcess2(int no);
void grandchildprocess1(int no);
void grandchildprocess2(int no);
void grandchildprocess3(int no);
void grandchildprocess4(int no);
void  ParentProcess(int no);
void greatgrandchild1(int no);
void greatgrandchild2(int no);
void greatgrandchild3(int no);
void greatgrandchild4(int no);
void greatgrandchild5(int no);
void greatgrandchild6(int no);
void greatgrandchild7(int no);
void greatgrandchild8(int no);
void  main()
{
     int num;
     scanf("%d",&num);
     ParentProcess(num);
}

void  ParentProcess(int no)
{
     pid_t  pid1,pid2,a,b;
    
     
     a=getpid();
     pid1 = fork();
     
     b=getpid();
     if(a==b){
     pid2 = fork();
     }
     
     if (pid1 == 0) 
          ChildProcess1(no);
     if(pid2 == 0)
         ChildProcess2(no);
}

void  ChildProcess1(int no)
{
    printf("Its child 1  process\n");
    pid_t pid3 , pid4,a,b;
    
    a=getpid();
     pid3 = fork();
     b=getpid();
     if(a==b){
     pid4 = fork();
     }
    
    if(pid3 == 0)    
        grandchildprocess1(no);
    if(pid4 == 0)
        grandchildprocess2(no);
    else
     {
      int   i;
      for (i = 1; i <= no; i++)
       {
          if(i%2!=0)
          {
           printf("**This is odd no from child 1 process , value = %d\n", i);
          }
       }
      
     }
}
void  ChildProcess2(int no)
{
    
    printf("Its child 1  process\n");
    pid_t pid5 , pid6,a,b;
    a=getpid();
     pid5 = fork();
     b=getpid();
     if(a==b){
     pid6 = fork();
     }
    if(pid5 == 0)    
        grandchildprocess3(no);
    if(pid6 == 0)
        grandchildprocess4(no);
    else
     {
      int   i;
      for (i = 1; i <= no; i++)
       {
          if(i%2!=0)
          {
           printf("**This is odd no from child 2 process , value = %d\n", i);
          }
       }
      
     }

}
void grandchildprocess1(int no)
 {
    
    pid_t pid7,pid8,a,b;
    a=getpid();
     pid7 = fork();
     b=getpid();
     if(a==b){
     pid8 = fork();
     }
    if(pid7==0)
      {
          greatgrandchild1(no);
      }
    if(pid8==0)
      {
         greatgrandchild2(no);
      }
   else
    {
      int i;
      for(i =0;i<no;i++)
      {
          if(i%2 ==0 )
           {
             // wait(1);
              printf("****this is even no produced by grand child 1. value = %d\n",i);
           }
      }
    }
}

void grandchildprocess2(int no)
 {
    pid_t pid9,pid10,a,b;
    a=getpid();
     pid9 = fork();
     b=getpid();
     if(a==b){
     pid10 = fork();
     }
    if(pid9==0)
     {
       greatgrandchild3(no);
     }
    if(pid10==0)
     {
       greatgrandchild4(no);
     }
    else
    {
    int i;
    for(i =0;i<no;i++)
      {
          if(i%2 ==0 )
           {
              printf("****this is even no produced by grand child 2. value = %d\n",i);
           }
      }
    }
   
}
void grandchildprocess3(int no)
 {
    pid_t pid11, pid12;
    if(pid11 ==0)
    {
      greatgrandchild5(no);
    }
    if(pid12 ==0)
    {
      greatgrandchild6(no);
    }
    else
    {
    int i;
    for(i =0;i<no;i++)
      {
          if(i%2 ==0 )
           {
              printf("****this is even no produced by grand child 3. value = %d\n",i);
           }
      }
    }
}
void grandchildprocess4(int no)
 {
   pid_t pid13, pid14;
   if(pid13==0)
   {
     greatgrandchild7(no);
   }
   if(pid14==0)
   {
     greatgrandchild8(no);
   }
   else
   { 
   int i;
    for(i =0;i<no;i++)
      {
          if(i%2 ==0 )
           {
              printf("****this is even no produced by grand child 4. value = %d\n",i);
           }
      }
   }
}

void greatgrandchild1(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 1. value = %d\n",i);
          }
     }
}

void greatgrandchild2(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 2. value = %d\n",i);
          }
     }
}

void greatgrandchild3(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 3. value = %d\n",i);
          }
     }
}

void greatgrandchild4(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 4. value = %d\n",i);
          }
     }
}
void greatgrandchild5(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 5. value = %d\n",i);
          }
     }
}

void greatgrandchild6(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 6. value = %d\n",i);
          }
     }
}

void greatgrandchild7(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 7. value = %d\n",i);
          }
     }
}

void greatgrandchild8(int no)
{
   int i;
   for(i=0;i<no;i++)
    {
        if(i%5==0)
          {
            printf("******this is divisible 5 no by great grandchild 8. value = %d\n",i);
          }
     }
}   

