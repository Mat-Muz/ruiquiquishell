#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>
#include "input.h"
#include "main.h"
#include "function.h"
#include "utilities.h"

Important_stuff Global_Vars;

void handle_sigchld(int sig) {
    (void)sig; // sto warning
    int status;
    pid_t pid;

    // enfant en bg
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("\n[%d] terminé.\n", pid);
    }

    // pour eviter le double prompt et afficher le prompt sinon 
    if (Global_Vars.fg == 0 && Global_Vars.cwd != NULL) {
        printf("(%s) $ ", Global_Vars.cwd);
        fflush(stdout);
    }
}


void a_line(){
    Global_Vars.First = input_to_comands_semi(Global_Vars.usertext);
    List_Commandes * Elem = Global_Vars.First;
    while (Elem != NULL)
    {
        Commande * current = Elem->curent;
        if(builtin(current) == 1 ){
            Elem = Elem->suiv;
            continue;
        }
        normal_command(current);
        Elem = Elem->suiv;
    }
    Clean_All(&Global_Vars, 0);
}



int main(int argc, char **argv) {
    Global_Vars.usertext = NULL;
    Global_Vars.First = NULL;
    Global_Vars.fg = 0;
    current_directory_update(&Global_Vars);

    struct sigaction sa;
    sa.sa_handler = handle_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    while (1) {
        printf("(%s) $ ", Global_Vars.cwd);
        fflush(stdout);

        Global_Vars.usertext = get_user_input();
        if (Global_Vars.usertext == NULL) {
            printf("\n");
            break; //on quitte si EOF comme dans bash
        }
        a_line();
    }

    Clean_All(&Global_Vars, 1);
    return 0;
}