

# EnseaSH — Micro Shell Project

## 📜 Project Overview

**EnseaSH** is a micro shell developed as a synthesis practical work ("TP de Synthèse") for the 2nd year of the Computer Science Major at **ENSEA**.

The primary objective of this project is to demonstrate a deep understanding of low-level system mechanisms, including process creation, signal handling, and file descriptor management. This shell mimics standard shell behaviors: executing commands, managing I/O, and monitoring execution metrics.

| **Context** | 2nd Year — Computer Science Major |
| :--- | :--- |
| **Institution** | ENSEA |
| **Authors** | **Agheles Mekdache** & **Salim Bouateli** |

-----

## 🚀 Implemented Features

This shell implements a robust set of functionalities, developed incrementally:

  * [x] **Welcome Message**
    Displays a welcome message and a prompt (`enseash %`) upon startup.
  * [x] **Command Execution**
    Supports simple commands (e.g., `ls`, `date`) and commands with arguments (e.g., `ls -l /tmp`).
  * [x] **REPL (Read-Eval-Print Loop)**
    Reads user input, executes it, and waits for the next command efficiently.
  * [x] **Exit Management**
    Cleanly exits the shell using the `exit` command or `<Ctrl>+d`.
  * [x] **Status Display**
    Shows the exit code or signal of the previous command in the prompt (e.g., `[exit:0]` or `[sign:9]`).
  * [x] **Execution Time Metrics**
    Measures and displays precise execution time using `clock_gettime` (e.g., `[exit:0|10ms]`).
  * [x] **I/O Redirections**
    Full support for Input (`<`) and Output (`>`) redirection.
  * [x] **Pipes**
    Supports inter-process communication via pipes (e.g., `ls | wc -l`).
  * [x] **Background Processes (Bonus)**
    Supports executing commands in the background using `&`.

-----

## 🛠 Technical Constraints & Standards

This project adheres to strict system programming constraints to ensure educational value and code quality:

  * **System Calls Only:** Standard I/O functions like `printf` are strictly avoided in favor of `write`.
  * **No `system()`:** Usage of the `system()` function is forbidden; the project relies entirely on the `exec` family functions.
  * **Clean Code Practices:** No "magic numbers," English variable naming conventions, and modular function design.
  * **Safe Memory & String Handling:** Usage of `string.h` and safe functions (e.g., `strn...`).

-----

## ⚙️ Installation & Usage

To compile and run the project on a Linux environment:

```bash
$ make
$ ./enseash
```

-----

## 💻 Code Snippet: Main Loop

Below is the entry point of the shell, demonstrating the REPL structure:

```c
#include "utils.h" 
int status;


int main(int argc, char *argv[]){
    char buffer[BUFFER_SIZE];
    char* args[MAX_ARGS];
    
    greetings();

      while (1) {
    
        print_prompt();
        ssize_t size = process_entry(buffer);
        char** command =build_command(buffer,args);
        execute_prompt(command);

    }

    return 0;
  }
```
