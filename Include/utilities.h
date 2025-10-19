#ifndef UTILITIES_H
#define UTILITIES_H
#include "main.h"

void Clean_List_Commandes(List_Commandes * First);

void Clean_All(Important_stuff * Vars, int clean_cwd);

void current_directory_update(Important_stuff * Vars);

#endif