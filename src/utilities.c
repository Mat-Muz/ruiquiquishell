#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
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