#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h" 


int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];

    print("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");


    while (1) {
   
        print("enseash/%");

        ssize_t size = read_entry(buffer);


        if (strcmp(buffer, "exit") == 0) {
            print("Bye bye...\n");
            exit(EXIT_SUCCESS);
        }

  


    }

    return 0;
}