
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024



void print(char* str){
    write(STDOUT_FILENO,str,strlen(str));

}

int read_entry(char* buffer){
    //we use the type ssize to have -1 to MAX/2 , we need the -1 in case of an error of read
    ssize_t ret = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1); 

    //if there is nothing left to read
    if (ret == 0) {
        print("Bye.....Bye....");
        exit(EXIT_SUCCESS); 
    } else if (ret < 0) {
        //in case of an error from the read function
        print("Erreur de lecture\n");
        exit(EXIT_FAILURE);
    }
    //we have to check eventual returns to line 
    if (buffer[ret - 1] == '\n') {
        buffer[ret - 1] = '\0';

    } else {
        //if there are no return to line then we juste check if the String ends properly
        buffer[ret] = '\0';
    }

    return ret;
}

