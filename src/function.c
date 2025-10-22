#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 
#include <fcntl.h>

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

        if (currentprog->fd_out != -1) { 
            if (dup2(currentprog->fd_out, STDOUT_FILENO) == -1) { //fd ou pipe[1]
            perror("dup2");
            _exit(1);
            }
        }
        if (currentprog->fd_in != -1) { 
            if (dup2(currentprog->fd_in, STDIN_FILENO) == -1) { //fd ou pipe[0]
            perror("dup2");
            _exit(1);
            }
        }
        close_fds(currentprog);
        execvp(currentprog->args[0], currentprog->args);
        perror("execvp");
        Clean_All(&Global_Vars, 1);
        exit(1);
        
    } else {
        //parent
        close_fds(currentprog);

        if (currentprog->background == 0) {
            int stat;
            waitpid(pid, &stat, 0);
        } else {
            printf("%d\n", pid);
        }
    }
}