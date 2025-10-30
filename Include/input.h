#ifndef INPUT_H
#define INPUT_H

#include "main.h"

string get_user_input(); //return user input in a form of string

List_Commandes *  input_to_comands_semi( char * ); //Sépare le texte du user en plusieures comandes

List_Commandes * parse_unecommande(string unecomande);

List_Commandes * input_to_commands_pipe( string userinput);


#endif