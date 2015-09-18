#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(){

    int nbytes;
    int fd1[2];
    pipe(fd1);

    pid_t f1=fork();//fork1 
      
    if(f1==-1){
        printf("Error in forking\n");
        return;
    }else if(f1==0){
        //child1
        
        FILE *fp2;
                    //while(1) {
                        
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
                    printf("%Lf\n",loadavg);
                    write(fd1[1], &loadavg, sizeof(loadavg));
                    printf("%Lf\n",loadavg);
    }else{
        //main -->fork2

        wait(f1);
        int rc;
        printf("Main");
                    //Parent process closes up output side of pipe 
                    
                      
        fd_set fds;
                      
                    //while(1) {
        close(fd1[1]);                  
        FD_ZERO(&fds);
        FD_SET(fd1[0], &fds);
                        /*FD_SET(fd2[0], &fds);
                        FD_SET(fd3[0], &fds);
                        FD_SET(fd4[0], &fds);*/
                            
                        rc = select(fd1[0]+1, &fds, NULL, NULL, NULL);
                            
                        if(FD_ISSET(fd1[0], &fds)) { 
                            long double loadavg;
                            nbytes=read(fd1[0], &loadavg, sizeof(loadavg));
                            printf("Received CPU usage: %Lf\n",loadavg);
                        }
        return 0;
    }

    return 0;
}