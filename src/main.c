#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
typedef char* string;

typedef struct{

    string cmd;
    int nbarg;
    string * args; //tableau de string
    string path; 


} Commande;


void exec(){
    char buff[512];
    fgets(buff,sizeof(buff),stdin);
    buff[strcspn(buff, "\n")] = '\0'; //Clean
    string tabcom[2];
    string unecommande = strtok(buff," ");
    tabcom[0] = unecommande;
    tabcom[1] = NULL;
    pid_t pid = fork();
    if (strcmp(unecommande,"exit") == 0 )
    {
        exit(0);
    }
    
    if (pid == -1)
    {
        perror("fork");
    }
    else if(pid == 0){
         execvp(tabcom[0], tabcom);
         perror("execvp"); 
         exit(1);
    }
    else{
        //daron
        int stat;
        waitpid(pid,&stat,0);
    }
    
}




int main(int argc, char ** argv){
    while(1){
    printf(">>");
    exec();
    }
    return 0;

}