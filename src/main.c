#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
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


void exec(){
    char buff[512];
    fgets(buff,sizeof(buff),stdin);
    buff[strcspn(buff, "\n")] = '\0'; //Clean
    Commande Prog;
    int capa = 2;
    Prog.args = (string*)malloc(sizeof(string)* capa);
    string tempoarg = strtok(buff," ");

    if (strcmp(tempoarg,"exit") == 0 )
    {
        free(Prog.args);
        exit(0);
    }
    Prog.nbarg = 0;
    while(tempoarg != NULL){
        if(Prog.nbarg > capa){ //on va doubler a chaque fois pour eviter de faire trop de realloc (les mec sur stack overflow il ont dit c'est ça quil daut faire)
            capa = capa*2;
            string * temp = realloc(Prog.args,sizeof(string)*capa);
            if(temp == NULL){
                perror("realloc");
                for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
                free(Prog.args);
                return;
            }
            Prog.args =temp;
        }
        Prog.args[Prog.nbarg] = strdup(tempoarg);
        Prog.nbarg++;
        tempoarg = strtok(NULL," ");
    }
    string * temp = realloc(Prog.args,sizeof(string)*(Prog.nbarg+1));
    if(temp == NULL){
        perror("realloc");
        for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
        free(Prog.args);
        return;       
    }
    Prog.args =temp;
    Prog.args[Prog.nbarg] = NULL;
    if(Prog.nbarg == 2 && strcmp(Prog.args[0],"cd") == 0 ){
        chdir(Prog.args[1]);
        for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
        free(Prog.args);
        return;
    }
    if(Prog.nbarg == 1 && strcmp(Prog.args[0], "pwd")==0){
        
        string cwd  = getcwd(NULL,0); //aloue tout seul a ala bonne taille
        printf("%s \n", cwd);
        free(cwd);
        for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
        free(Prog.args);
        return;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if(pid == 0){
        execvp(Prog.args[0], Prog.args);
        perror("execvp"); 
        for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
        free(Prog.args);
        exit(1);
    }
    else{
        //daron
        int stat;
        waitpid(pid,&stat,0);
        for (int i = 0; i < Prog.nbarg; i++) free(Prog.args[i]);
        free(Prog.args);
    }
    
}




int main(int argc, char ** argv){
    while(1){
    printf("$");
    exec();
    }
    return 0;
}