#include "input.h"
#include "utilities.h"
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


int detect_background(Commande * Prog){
    if(Prog->nbarg ==0){
        return 0;
    }
    int lenoflast = strlen(Prog->args[Prog->nbarg -1]);
    if(strcmp(Prog->args[Prog->nbarg -1],"&") == 0){ //Cas ou le & est tout seul
        free(Prog->args[Prog->nbarg -1]);
        Prog->args[Prog->nbarg -1] = NULL;
        Prog->nbarg--;
        return 1;
    }
    else if(Prog->args[Prog->nbarg -1][lenoflast -1] == '&'){ //Cas ou le & est collé a la fin du mot
        Prog->args[Prog->nbarg -1][lenoflast -1] = '\0';
        return 1;
    }
    return 0;
}


List_Commandes * parse_unecommande(string unecomande){
    List_Commandes * Coms = (List_Commandes *) malloc(sizeof(List_Commandes));
    if(Coms == NULL ){
        perror("malloc error in input_to_commands");
        return NULL;          
    }
    

    Coms->suiv = NULL;
    Coms->curent = (Commande * )malloc(sizeof(Commande));
    Commande  * Prog = Coms->curent;
    
    int capa = 2;
    Prog->args = (string*)malloc(sizeof(string)* capa);
    Prog->nbarg = 0;
    


    Prog->redirect_file = check_plusgrand(unecomande);

    char * saveptr1;
    string tempoarg = strtok_r(unecomande," ", &saveptr1); //strtok_r pour eviter les problme de strtok imbrqué



    while(tempoarg != NULL){
        if(Prog->nbarg >= capa){ //on va doubler a chaque fois pour eviter de faire trop de realloc (les mec sur stack overflow il ont dit c'est ça quil daut faire)
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
        tempoarg = strtok_r(NULL," ", &saveptr1);
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
    else Prog->background = detect_background(Prog);

    return Coms;

}


List_Commandes *  input_to_comands( char * userinput){
    /*
    input_to_command seppare le userinput en sous commandes graces aux ;
    */

    List_Commandes * First = NULL;
    char * saveptr2;
    string unecomande = strtok_r(userinput,";", &saveptr2); //strtok_r pour eviter les problme de strtok imbrqué
    if(unecomande == NULL){
        return NULL;
    }
    First = parse_unecommande(unecomande);
    if(First == NULL){
        return NULL;
    }
    List_Commandes * Elem = First;
    while ((unecomande = strtok_r(NULL,";", &saveptr2)) != NULL)
    {
        Elem->suiv = parse_unecommande(unecomande);
        if(Elem->suiv == NULL){
            break;
        }        
        Elem = Elem->suiv;
    }
    return First;

}
