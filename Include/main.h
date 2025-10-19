#ifndef MAIN8H
#define MAIN8H



typedef char* string;


typedef struct{

    string cmd;
    int nbarg; //avec commande sans null
    string * args; //tableau de string commande + NULL
    int background; //c"est pour le &


} Commande;

typedef struct LComandes{
    Commande  * curent;
    struct LComandes * suiv;


} List_Commandes;



typedef struct {
    string usertext;
    List_Commandes * First;
    string cwd; 

}Important_stuff; //plus simple a free car variable golbale

extern Important_stuff Global_Vars;

#endif
