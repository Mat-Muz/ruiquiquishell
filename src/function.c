#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

int builtin(Commande * currentprog){
    

    if (strcmp(currentprog->args[0],"exit") == 0 )
    {   
        Clean_All(&Global_Vars,1);
        exit(0);
    }
    if(currentprog->nbarg == 2 && strcmp(currentprog->args[0],"cd") == 0 ){
        chdir(currentprog->args[1]);
        current_directory_update(&Global_Vars);
        return 1;
    }
    if(currentprog->nbarg == 1 && strcmp(currentprog->args[0], "pwd")==0){
        
        string cwd  = Global_Vars.cwd; //aloue tout seul a ala bonne taille
        printf("%s \n", cwd);
        return 1;
    }
    return 0;
}

void normal_command(Commande * currentprog) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        //enfant
        execvp(currentprog->args[0], currentprog->args);
        perror("execvp");
        Clean_All(&Global_Vars, 1);
        exit(1);
        
    } else {
        //parent
        if (currentprog->background == 0) {
            int stat;
            waitpid(pid, &stat, 0);
        } else {
            printf("%d\n", pid);
        }
    }
}