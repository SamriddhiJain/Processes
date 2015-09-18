#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2], fd2[2], nbytes;
        pid_t   childpid, childpid2;

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                return(1);
        }

        if(childpid == 0)
        {
        	     int i, j;
			char map[37][2], a, b;
			FILE *fp = fopen("charMap.txt", "r"); 
			for(i = 0; i < 37; i++) {
				fscanf(fp, "%c%*c%c%*c", &map[i][0], &map[i][1]);
				//cout<<map[i][0]<<map[i][1];
			}
			fclose(fp);
                close(fd[0]);
			
                /* Child process closes up input side of pipe */
                while(1) {
                
      		  char    string[80];
                printf("Enter your String: ");
                scanf("%s", string);
                for(i = 0; i < sizeof(string); i++) {
                for(j = 0; j < 37; j++) {
						if(string[i] == map[j][0]) {
							string[i] = map[j][1];
							break;
						}
					}
                }
                /* Send "string" through the output side of pipe */
                write(fd[1], string, (sizeof(string)));
                }
                //return(0);
        }
        else
        {	
        	  pipe(fd2);
              if((childpid2 = fork()) == 0) {
              	close(fd2[0]);
              	FILE *fp2;
              	while(1) {
              		long double a[4], b[4], loadavg;
				  
				  char dump[50];
				  sleep(10);
				  //for(;j<10;j++) {
					  fp2 = fopen("/proc/stat","r");
					  fscanf(fp2,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
					  fclose(fp2);
					  sleep(1);

					  fp2 = fopen("/proc/stat","r");
					  fscanf(fp2,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
					  fclose(fp2);

					  loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
					  write(fd2[1], &loadavg, sizeof(loadavg));
					  //sleep(10);
				  //}
              		
              	}
              } else {
		          //sleep(10);
		          FILE *fp, *fp2, *fp3;
		          int rc, rc1;
		          /* Parent process closes up output side of pipe */
		          close(fd[1]);
		          close(fd2[1]);
		          
		          fd_set fds;
		          /*FD_ZERO(&fds);
		          
		          FD_SET(fd[0], &fds);
		          FD_SET(fd2[0], &fds);*/
		          
		          while(1) {
		          	    
		          	FD_ZERO(&fds);
		                FD_SET(fd[0], &fds);
		                FD_SET(fd2[0], &fds);
		          	    
		                rc = select(fd[0] + fd2[0] + 1, &fds, NULL, NULL, NULL);
		                //rc1 = select(fd2[0]+ 1, &fds2, NULL, NULL, NULL);
		                
		                if(FD_ISSET(fd[0], &fds)) {
				    	    fp = fopen("Child1.txt", "a");		
			  		    char readbuffer[80];
					    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
					    fprintf(fp, "Received string: %s\n", readbuffer);
					    fclose(fp);
				    }
				    
				    if(FD_ISSET(fd2[0], &fds)) {
					    long double loadavg;
					    fp2 = fopen("Child2.txt", "a");
					    read(fd2[0], &loadavg, sizeof(loadavg));
		  			    fprintf(fp2, "Received CPU usage: %Lf\n",loadavg);
					    fclose(fp2);
				    }
				    
		          }
                }
        }
        
        return(0);
}
