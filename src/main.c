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
    (void)sig; // stop warning
    int status;
    pid_t pid;


    // nettoie tous les processus enfants terminés
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) { //WNOHANG pour ne pas bloquer si pas d'enfant terminé
        printf("\n enfant %d fini.\n", pid);
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
            break; //on quitte si EOF comme dans terminal
        }
        a_line();
    }

    Clean_All(&Global_Vars, 1);
    return 0;
}