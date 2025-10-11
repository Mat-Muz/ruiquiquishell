#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

int builtin(List_Commandes * First, Commande * currentprog){
    

    if (strcmp(currentprog->args[0],"exit") == 0 )
    {   
        //xlean all
        free(currentprog->args);
        exit(0);
    }
    if(currentprog->nbarg == 2 && strcmp(currentprog->args[0],"cd") == 0 ){
        chdir(currentprog->args[1]);
        for (int i = 0; i < currentprog->nbarg; i++) free(currentprog->args[i]);
        free(currentprog->args);
        return 1;
    }
    if(currentprog->nbarg == 1 && strcmp(currentprog->args[0], "pwd")==0){
        
        string cwd  = getcwd(NULL,0); //aloue tout seul a ala bonne taille
        printf("%s \n", cwd);
        free(cwd);
        for (int i = 0; i < currentprog->nbarg; i++) free(currentprog->args[i]);
        free(currentprog->args);
        return 1;
    }
    return 0;
}

void normal_command(Commande * currentprog ,int background){

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if(pid == 0){
        execvp(currentprog->args[0], currentprog->args);
        perror("execvp"); 
        for (int i = 0; i < currentprog->nbarg; i++) free(currentprog->args[i]);
        free(currentprog->args);
        exit(1);
        
    }
    else{
        //daron
        int stat;
        if(background == 0){
        waitpid(pid,&stat,0);
        }
        //free all
        for (int i = 0; i < currentprog->nbarg; i++) free(currentprog->args[i]);
        free(currentprog->args);
    }

}