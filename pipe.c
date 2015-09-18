#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){

    int nbytes;
    int fd1[2],fd2[2],fd3[2],fd4[2];
    pipe(fd1);

    pid_t f1=fork();//fork1 
      
    if(f1==-1){
        printf("Error in forking\n");
        return;
    }else if(f1==0){
        //child1
        
        int i,j;
        char table[37][2];

        FILE* ftable=fopen("charMap.txt","r");
        for(i=0;i<37;i++){
            fscanf(ftable,"%c%*c%c%*c",&table[i][0],&table[i][1]);
        }
        fclose(ftable);

        char str[30];

        dup2(0,fd1[0]);

        printf("Enter the string\n");
        scanf("%s",str);

        for(i=0;i<strlen(str);i++){
            for(j=0;j<37;j++){
                if(str[i]==table[j][0]){
                    str[i]=table[j][1];
                    break;
                }
            }
        }

        //printf("%s\n",str);
        write(fd1[1],str,strlen(str));
        
        return;
    }else{
        //main -->fork2
        wait(f1);

        pipe(fd2);
        pid_t f2=fork();

        if(f2==-1){
            printf("Error in forking\n");
            return;

        }else if(f2==0){
            //child2

            dup2(0,fd2[0]);
            int i;
            char str[30];
            printf("Enter name of file:\n");
            scanf("%s",str);

            write(fd2[1],str,strlen(str));

            return;
        }else{
            //main-->fork3
            wait(f2);

            pipe(fd3);
            pid_t f3=fork();

            if(f3==-1){
                printf("Error in forking\n");
                return;
            }else if(f3==0){
                //child3
                
                char ch,str[30];
                char data[100];
                int i=0;
                dup2(0,fd3[0]);

                printf("Enter the file name to be copied:\n");
                scanf("%s",str);

                FILE* f1=fopen(str,"r");
                while((ch=fgetc(f1)) != EOF){
                    data[i++]=ch;
                }
                data[i]='\0';

                write(fd3[1],data,sizeof(data));

                return;
            }else{
                //main-->fork4
                pipe(fd4);

                wait(f3);
                pid_t f4=fork();

                if(f4==-1){
                    printf("Error in forking\n");
                    return;
                }else if(f4==0){
                    //child4
                
                    FILE *fp2;
                    while(1) {
                        
                    long double a[4], b[4], loadavg;
                  
                    sleep(1);

                    fp2 = fopen("/proc/stat","r");
                    fscanf(fp2,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
                    fclose(fp2);
                    sleep(1);

                    fp2 = fopen("/proc/stat","r");
                    fscanf(fp2,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
                    fclose(fp2);

                    loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));

                    write(fd4[1], &loadavg, sizeof(loadavg));
                    //printf("%Lf\n",loadavg);

                    //close(fd4[0]);
                    } 
                    
                    return 0; 
                }else{
                    //main
                    int rc;
                    //wait(f4);
                    
                    printf("\n\n***********************Main*************************\n");
                    printf("****************************************************\n\n");
                    //Parent process closes up output side of pipe 
                    close(fd1[1]);
                    close(fd2[1]);
                    close(fd3[1]);
                    close(fd4[1]);
                      
                    fd_set fds;
                      
                    while(1) {
                            
                        FD_ZERO(&fds);
                        FD_SET(fd1[0], &fds);
                        FD_SET(fd2[0], &fds);
                        FD_SET(fd3[0], &fds);
                        FD_SET(fd4[0], &fds);
                            
                        rc = select(fd1[0]+fd2[0]+fd3[0]+fd4[0]+1, &fds, NULL, NULL, NULL);
                            
                        if(FD_ISSET(fd1[0], &fds)) {   
                            close(fd1[1]);  
                            char arr[30];
                            int i;
                            nbytes=read(fd1[0], arr, sizeof(arr));

                            printf("Child1: Modified String: ");
                            for(i=0;i<nbytes;i++){
                                printf("%c",arr[i] );
                            }
                            printf("\n");
                        }

                        if(FD_ISSET(fd2[0], &fds)) {   
                            char arr[30];
                            int i;
                            nbytes=read(fd2[0], arr, sizeof(arr));
                            char fname[nbytes+1];

                            //printf("%d\n",nbytes );
                            printf("Child2: File Name: ");

                            for(i=0;i<nbytes;i++){
                                fname[i]=arr[i];
                                printf("%c",arr[i] );
                            }
                            //fname[i+1]='\0';
                            printf("\n");

                            //execlp("espeak", "espeak", fname, (void*)0);
                            char *result = (char*)malloc(12+nbytes);    
                            strcpy(result,"espeak -f ");
                            strcat(result, fname);
                            system(result);
                        }

                        if(FD_ISSET(fd3[0], &fds)) {   
                            char arr[100];
                            int i=0;
                            nbytes=read(fd3[0], arr, sizeof(arr));
                            //printf("%d\n",nbytes );

                            FILE* fnew=fopen("copy.txt","w");
                            fprintf(fnew,"%s\n",arr);
                            printf("Child3: File successfully copied.\n");

                            fclose(fnew);            
                        }
                        
                        if(FD_ISSET(fd4[0], &fds)) { 
                            long double loadavg;
                            nbytes=read(fd4[0], &loadavg, sizeof(loadavg));
                            printf("Child4: Received CPU usage: %Lf\n",loadavg);
                        }
                        
                    }
                    wait();
                    return 0;
                }
            }
        }
    }

    return 0;
}