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
    
    if (buffer[ret - 1] == '\n') {
        buffer[ret - 1] = '\0';

    } 
    else {
        buffer[ret] = '\0';
    }

    return ret;
}

char* build_command(char*buffer){
    return strtok(buffer," \n");  

}


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



        
void execute_prompt(char* command){

    clock_gettime(CLOCK_MONOTONIC,&start);
    
    if (strcmp(command, "exit") == 0) {
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
            execlp(command, command, (char *)NULL);
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



