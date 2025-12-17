#include "utils.h" 

extern int status;
struct timespec start, end;

void print(char* str){
    write(STDOUT_FILENO, str, strlen(str));
}


int process_entry(char* buffer){
    ssize_t ret = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1); 

   
    if (ret == 0) {        
        exit(EXIT_SUCCESS); 
    } 
    
    else if (ret < 0) {
   
        print("Erreur de lecture\n");
        exit(EXIT_FAILURE);
    }
    // Terminates the process if the Enter key is detected
    if (buffer[ret - 1] == '\n') {
        buffer[ret - 1] = '\0';

    } 
    else {
        buffer[ret] = '\0';
    }

    return ret;
}

char** build_command(char*buffer, char* args[]){
    int i = 0;
    //strtok parses a String into tokens following the list of delimiters given , here " " and "\n"
    char *token = strtok(buffer, " \n");
    
    while (token != NULL) {
        
        args[i] = token; 
        i++;
        
        if (i >= MAX_ARGS - 1) break; 
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;


    return args ;  

}


/* 
The function builds the prompt string with exit status (EXIT/SIG) and time difference (ms).
It uses WIFEXITED/WIFSIGNALED macros on 'status'.
*/

char* build_prompt() {
    
    double time_diff_ms;

    static char buffer[MAX_STATUS_MSG_SIZE]; 
    const char *first_part = "enseash[";
    const char *exit_str = "EXIT:";
    const char *sig_str = "SIG:"; 
    const char * middle_part=" |";
    const char *last_part = "ms ]%";

    
    if(WIFEXITED(status)) {

        int result_of_the_child = WEXITSTATUS(status);


        
        time_diff_ms=(end.tv_sec - start.tv_sec) * 1000.0 + 
                (end.tv_nsec - start.tv_nsec) / 1000000.0;


        // "enseash[" + "EXIT:" + number + "]%"
        int len = snprintf(buffer, MAX_STATUS_MSG_SIZE, "%s%s%d%s%.1f%s", 
                           first_part, exit_str, result_of_the_child,middle_part,time_diff_ms, last_part);
        
     
        if (len < 0 || len >= MAX_STATUS_MSG_SIZE) {
            return NULL; 
        }
        
        return buffer;

    } 

    else if (WIFSIGNALED(status)) {
        int process_killer = WTERMSIG(status);

        time_diff_ms=(end.tv_sec - start.tv_sec) * 1000.0 + 
                (end.tv_nsec - start.tv_nsec) / 1000000.0;


        // Construct the final string safely: "enseash[" + "SIG:" + number + "]%"
        int len = snprintf(buffer, MAX_STATUS_MSG_SIZE, "%s%s%d%s%.1f%s", 
                           first_part, sig_str, process_killer,middle_part,time_diff_ms, last_part);

        if (len < 0 || len >= MAX_STATUS_MSG_SIZE) {
            return NULL; 
        }

        return buffer;
    }
    
    
    else {
        snprintf(buffer, MAX_STATUS_MSG_SIZE, "%sUNKNOWN]%s", first_part, last_part);
        return buffer;
    }

}


void print_prompt(){
    
    print(build_prompt());

    
}

/*
The function finds '<' or '>', opens the file, uses dup2 to redirect STDIN/STDOUT, and clears the args.
*/

void redirect_and_filter_args(char** args){

    for (int i = 0; args[i]!=NULL;i++){
                
        if(strcmp(args[i],"<")==0){
            if (args[i+1] == NULL) {
                print("Erreur: pas de fichier après <\n");
                exit(EXIT_FAILURE);
            }
            args[i]=NULL;

            int fd = open(args[i+1], O_RDONLY);
                    
            args[i+1]=NULL;

            if (fd == -1) {
                perror("open");
                exit(1);
                }

            dup2(fd, STDIN_FILENO);
                    
            close(fd);
                
            }
        if(strcmp(args[i],">")==0){
            if (args[i+1] == NULL) {
                print("Erreur: pas de fichier après >\n");
                exit(EXIT_FAILURE);
            }
            args[i]=NULL;

            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    
            args[i+1]=NULL;

            if (fd == -1) {
                perror("open");
                exit(1);
                }

        dup2(fd, STDOUT_FILENO); 
        close(fd);

        }
        //question 8 



            }

}
        

void execute_prompt(char** command){

    if (command[0] == NULL) {
        return; 
    }
    clock_gettime(CLOCK_MONOTONIC,&start);
    
    if (strcmp(command[0], "exit") == 0) {
        print("Bye bye...\n");
        exit(EXIT_SUCCESS);
    }
    else {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Erreur fork");
        } 
        else if (pid == 0) {
            // ===(CHILD) ===
            redirect_and_filter_args(command);
            execvp(command[0], command);
            perror("Erreur d'execution");
            exit(EXIT_FAILURE); 
        } 
        else {
            // === (PARENT/SHELL) ===
            waitpid(pid, &status, 0);
        }

    }

    clock_gettime(CLOCK_MONOTONIC,&end);
    
}
