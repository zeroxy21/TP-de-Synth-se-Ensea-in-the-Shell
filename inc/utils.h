#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h> 

#define BUFFER_SIZE 1024
#define MAX_STATUS_MSG_SIZE 30
#define MAX_ARGS 64

void print(char* str);
void print_prompt();
int process_entry(char* buffer);
char* build_prompt();
void execute_prompt(char** command);
char** build_command(char*buffer,char* args[]);
void redirect_and_filter_args(char** args);
void build_and_execute_pipe(char** command); 
bool check_pipe(char** command);
void greetings();
