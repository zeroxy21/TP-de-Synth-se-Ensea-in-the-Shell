
#include "utils.h" 
int status;


int main(int argc, char *argv[]){
    char buffer[BUFFER_SIZE];
    char* args[MAX_ARGS];

    print("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");

      while (1) {
        
        print_prompt();
        ssize_t size = process_entry(buffer);
        char** command =build_command(buffer,args);
        execute_prompt(command);

    }

    return 0;
}