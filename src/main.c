#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "input.h"
#include "main.h"
#include "function.h"

void a_line(){
    string usertext = get_user_input();
    List_Commandes * First = input_to_comands(usertext);
    List_Commandes * Elem = First;

    while (Elem != NULL)
    {
        Commande * current = Elem->curent;
        int background = 0;
        if(builtin(First, current) == 1 ){
            Elem = Elem->suiv;
            continue;
        }
        normal_command(current, background);
        Elem = Elem->suiv;
    }
    
}




int main(int argc, char ** argv){
    while(1){
    printf("$");
    a_line();
    }
    return 0;
}