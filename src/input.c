#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * get_user_input(){
    char * buff = malloc(512*sizeof(char));
    if(buff == NULL){
        perror("malloc error in get_user_input");
    }
    fgets(buff,512,stdin);
    buff[strcspn(buff, "\n")] = '\0'; 
    return buff;
}

List_Commandes *  input_to_comands( char * userinput){
    List_Commandes * Coms = (List_Commandes *) malloc(sizeof(List_Commandes));
    if(Coms == NULL ){
        perror("malloc error in input_to_commands");
        return NULL;          
    }
    

    //
    Coms->suiv = NULL;
    Coms->curent = (Commande * )malloc(sizeof(Commande));
    Commande  * Prog = Coms->curent;
    
    int capa = 2;
    Prog->args = (string*)malloc(sizeof(string)* capa);
    Prog->nbarg = 0;

    string tempoarg = strtok(userinput," ");
    while(tempoarg != NULL){
        if(Prog->nbarg > capa){ //on va doubler a chaque fois pour eviter de faire trop de realloc (les mec sur stack overflow il ont dit c'est ça quil daut faire)
            capa = capa*2;
            string * temp = realloc(Prog->args,sizeof(string)*capa);
            if(temp == NULL){
                perror("realloc");
                for (int i = 0; i < Prog->nbarg; i++) free(Prog->args[i]);
                free(Prog->args);
                return NULL;
            }
            Prog->args =temp;
        }
        Prog->args[Prog->nbarg] = strdup(tempoarg);
        Prog->nbarg++;
        tempoarg = strtok(NULL," ");
    }
    string * temp = realloc(Prog->args,sizeof(string)*(Prog->nbarg+1)); //dans une tempo pour eviter de operdre l'adresse de Prog->args au cas ou pour free
    if(temp == NULL){
        perror("realloc");
        for (int i = 0; i < Prog->nbarg; i++) free(Prog->args[i]);
        free(Prog->args);
        return NULL;       
    }
    Prog->args =temp;
    Prog->args[Prog->nbarg] = NULL;
    if(Prog->nbarg == 0){
        free(Prog->args);
        free(Prog);
        free(Coms);
        Coms = NULL;
    }
    return Coms;

}




