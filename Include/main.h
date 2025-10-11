#ifndef MAIN8H
#define MAIN8H


typedef char* string;

typedef struct{

    string cmd;
    int nbarg; //avec commande sans null
    string * args; //tableau de string commande + NULL


} Commande;

typedef struct LComandes{
    Commande  * curent;
    struct LComandes * suiv;

} List_Commandes;


#endif