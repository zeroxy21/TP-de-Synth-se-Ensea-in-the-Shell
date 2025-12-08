#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h" 


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






        }
  


    }

    return 0;
}