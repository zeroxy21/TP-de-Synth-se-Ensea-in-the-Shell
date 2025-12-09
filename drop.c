#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h" 
#include <sched.h>

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];

    print("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");
      while (1) {
   
        print("enseash%");
        //to be safe we take a type ssize [-1,2¹5-1]
        ssize_t size = read_entry(buffer);
        //to filter spaces
        char* commande =strtok(buffer," \n");  



        if (strcmp(commande, "exit") == 0) {
            print("Bye bye...\n");
            exit(EXIT_SUCCESS);
        }

        //extern commands 
        else {

            if(strcmp(commande,"fortune")==0){
                fortune();
            }   
            // 1. On crée un nouveau processus (un clone du shell)
            pid_t pid = fork();

            if (pid == -1) {
                perror("Erreur fork"); // Échec de la création du processus
            } 
            else if (pid == 0) {
                // === PROCESSUS FILS (CHILD) ===
                // C'est ici qu'on remplace le shell par la commande
                
                // execlp cherche 'commande' dans le PATH
                // On passe 'commande' deux fois : 
                // 1 fois pour le chemin, 1 fois pour argv[0]
                execlp(commande, commande, (char *)NULL);

                // Si le code arrive ici, c'est que la commande n'existe pas
                perror("Erreur d'execution");
                exit(EXIT_FAILURE); // On tue le fils proprement
            } 
            else {
                // === PROCESSUS PÈRE (PARENT/SHELL) ===
                // Le shell doit attendre que le fils ait fini
                int status;
                waitpid(pid, &status, 0);
            }

        }

    }

    return 0;
}