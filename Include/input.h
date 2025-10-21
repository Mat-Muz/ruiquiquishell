#ifndef INPUT_H
#define INPUT_H

#include "main.h"

char * get_user_input(); //return user input in a form of string

List_Commandes *  input_to_comands( char * ); //Sépare le texte du user en plusieures comandes

List_Commandes * parse_unecommande(string unecomande);


#endif