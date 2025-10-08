#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
typedef char* string;

typedef struct{

    string cmd;
    int nbarg;
    string * args; //tableau de string
    string path; 


} Commande;



int main(int argc, char ** argv){

    char buff[512];
    fgets(buff,sizeof(buff),stdin);
    buff[strcspn(buff, "\n")] = '\0';
    printf(" ce que tu as écrit %s \n", buff);
    exit(EXIT_SUCCESS);
    return 0;

}