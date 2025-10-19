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

void a_line(){
    Global_Vars.usertext = get_user_input();
    Global_Vars.First = input_to_comands(Global_Vars.usertext);
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




int main(int argc, char ** argv){
    Global_Vars.usertext = NULL;
    Global_Vars.First = NULL;
    current_directory_update(&Global_Vars);
    while(1){
    printf("%s$ ",Global_Vars.cwd);
    a_line();
    }
    Clean_All(&Global_Vars, 1);
    return 0;
}