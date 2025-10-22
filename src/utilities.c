#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "utilities.h"




void Clean_List_Commandes(List_Commandes * First){
    List_Commandes * temp = First;
    while(temp != NULL){
        Commande * com_tofree = temp->curent;
        if (com_tofree != NULL) {
            if (com_tofree->args != NULL) {
                for (int i = 0; i < com_tofree->nbarg; i++){
                    if (com_tofree->args[i] != NULL) {
                        free(com_tofree->args[i]);
                        com_tofree->args[i] = NULL;
                    }
                }
                free(com_tofree->args);
                com_tofree->args = NULL;
            }
            free(com_tofree);
            com_tofree = NULL;
        }
        List_Commandes * Elem_tofree = temp;
        temp = temp->suiv;
        free(Elem_tofree);
        Elem_tofree = NULL;
    }
}

void Clean_All(Important_stuff * Vars, int clean_cwd){
    if(Vars == NULL) return;

    if(Vars->usertext != NULL){
        free(Vars->usertext);
        Vars->usertext = NULL;
    }
    if(Vars->First != NULL){
        Clean_List_Commandes(Vars->First);
        Vars->First = NULL;
    }
    if(clean_cwd == 1 && Vars->cwd != NULL){
        free(Vars->cwd);
        Vars->cwd = NULL;
    }

}

void current_directory_update(Important_stuff * Vars){
    if(Vars->cwd != NULL){
        free(Vars->cwd);
        Vars->cwd = NULL;
    }
    Vars->cwd = getcwd(NULL,0);
}

int check_plusgrand(string text){
        /*Detection de > pour redirection fichier*/

    char * redir_pos = strchr(text, '>');
    if (redir_pos != NULL) {
        *redir_pos = '\0'; // Terminer la commande avant '>'
        redir_pos++;
        while (*redir_pos == ' ') redir_pos++; // Ignorer les espaces pour nom du fichier
        char * end_pos = strpbrk(redir_pos, " "); // Trouver la fin du nom du fichier
        if (end_pos != NULL) {
            *end_pos = '\0'; 
        }
        return open(redir_pos, O_CREAT | O_WRONLY | O_TRUNC, 0644); // Ouvrir le fichier en écriture    
    } else {
        return -1; // Pas de redirection
    }
}


void close_fds(Commande * Prog){
    if(Prog->fd_in != -1){
        close(Prog->fd_in);
        Prog->fd_in = -1;
    }
    if(Prog->fd_out != -1){
        close(Prog->fd_out);
        Prog->fd_out = -1;
    }
}


void init_Prog(Commande * Prog){
    //initialisation de la structure commande
    Prog->cmd = NULL;
    Prog->nbarg = 0;
    Prog->args = NULL;
    Prog->background = 0;
    Prog->fd_in = -1;
    Prog->fd_out = -1;
}