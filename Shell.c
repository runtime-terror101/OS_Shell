#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>    //for fork, r_ok
#include<sys/wait.h>


int main(){
    printf("_________________________Welcome______________________________");
    char input[100];
    char juhi[100][100];
    char history[100][100];
    char cwd[1000];
    char his_ptr = 0;
    int leave = 0;      //for external commands
    int result = 5;
    while(1){
        printf("\n");
        printf(">>>");    //prompt
        scanf("%[^\n]%*c",input);
        strcpy(history[his_ptr],input);
        his_ptr++;

        //use strtok
        char *token;
		char* useless = input;
		int i=0;
		while ((token = strtok_r(useless, " ", &useless))){
			strcpy(juhi[i],token);
	    	i++;
		}

        if(strcmp(juhi[0],"history")==0){	                //history
            for(int y = 0; y<his_ptr ;y++){
                printf("%s\n",history[y]);
                memset(juhi, 0, sizeof juhi);
				leave++;                                 
            }
        }
/////////////////////////////////////////////////////////////////////////
        else if(strcmp(juhi[0],"cd")==0){			         // cd
			chdir(juhi[1]);
			getcwd(cwd,sizeof(cwd));
			
			printf("%s\n",cwd);
            memset(juhi, 0, sizeof juhi);
			leave++;                                      
		}
/////////////////////////////////////////////////////////////////////////
        else if(strcmp(juhi[0],"pwd")==0){			      // pwd
			getcwd(cwd,sizeof(cwd));
			printf("%s\n",cwd);
            memset(juhi, 0, sizeof juhi);
			leave++;
		}


//////////////////////////////////////////////////////////////////////////
        else if(strcmp(juhi[0],"echo")==0){		// echo
			for(int x=1; x<i; x++){
				if(juhi[x][0]==34)       //find quotes using ascii value
					continue;
	
				printf(" ");
				for(int y=0; y<strlen(juhi[x]); y++){
					if(juhi[x][y]==34)
						continue;
					printf("%c",juhi[x][y]);
				}
				
			}
			printf("\n");
            memset(juhi, 0, sizeof juhi);
			leave++;
		}
////////////////////////////////////////////////////////////////////////////

        else if(strcmp(juhi[0],"exit")==0){				// exit
			printf("----------------------END----------------------------");
            printf("/n");
            leave++;
			exit(0);
		}

/////////////////////////////////////////////////////////////////////////////

        if(leave == 0){
		char bin[] = "/bin/";
		strcat(bin,juhi[0]);

		result = access(bin,F_OK);	// checks if command is in /usr/bin 	

		int pid = fork();
			if(pid == 0){
				if(juhi[1][0] == '\0'){
					execlp(bin,juhi[0],juhi[1][0],(char*)0);
                    memset(juhi, 0, sizeof juhi);
				}
				
				else if(juhi[2][0] == '\0'){
					execlp(bin,juhi[0],juhi[1],(char*)0);
                    memset(juhi, 0, sizeof juhi);
				}

				else if(juhi[3][0] == '\0'){
						execlp(bin,juhi[0],juhi[1],juhi[2],(char*)0);
                        memset(juhi, 0, sizeof juhi);
				}

				else if(juhi[4][0] == '\0'){
						execlp(bin,juhi[0],juhi[1],juhi[2],juhi[3],(char*)0);
                        memset(juhi, 0, sizeof juhi);
				}

	
		
			}
	
			
			else           //make parent process wait
				{
					wait(0);             
				}
				
		
				leave++;

		}
        if(result==-1)
			printf("Not found");
		
        result += 5;
		leave = 0;
		

    }
    return 0;
}