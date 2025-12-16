# EnseaSH — Micro Shell Project

## 📜 Description

**EnseaSH** is a micro shell developed as a synthesis practical work ("TP de Synthèse") for the 2nd year of the Computer Science Major at **ENSEA**.

The goal of this project is to understand the low-level mechanisms of a shell, including process creation, signal handling, and file descriptor management. This shell executes commands, displays their exit codes/signals, and measures their execution time.

**Course:** 2nd Year — Computer Science Major  
**Authors:** Agheles Mekdache & Salim Bouateli

---

## 🚀 Features

This shell implements the following functionalities, developed incrementally:

1. **Welcome Message**  
   Displays a welcome message and a prompt (`enseash %`) upon startup.

2. **Command Execution**  
   - Supports simple commands (e.g., `ls`, `date`)  
   - Supports commands with arguments (e.g., `ls -l /tmp`)

3. **REPL (Read-Eval-Print Loop)**  
   Reads user input, executes it, and waits for the next command.

4. **Exit Management**  
   Cleanly exits the shell using the `exit` command or `<Ctrl>+d`.

5. **Status Display**  
   Shows the exit code or signal of the previous command in the prompt (e.g., `[exit:0]` or `[sign:9]`).

6. **Execution Time**  
   Measures and displays the execution time of commands using `clock_gettime` (e.g., `[exit:0|10ms]`).

7. **Redirections**  
   - Input redirection (`<`)  
   - Output redirection (`>`)

8. **Pipes**  
   Supports piping between two commands (e.g., `ls | wc -l`).

9. **Background Processes (Bonus)**  
   Supports executing commands in the background using `&`.

---

## 🛠 Technical Constraints

- **No `printf`**: Standard I/O functions like `printf` are avoided in favor of `write`.  
- **No `system()`**: `system` is forbidden; `exec` family functions are used instead.  
- **Code Quality**: No "magic numbers," clean English variable naming, modular functions.  
- **String Manipulation**: Usage of `string.h` and safe functions like `strn...`.

---


## How to use the project on linux:
```bash
   make
   ./enseash
```

## Main function:
```bash
int main(int argc, char *argv[]){
    char buffer[BUFFER_SIZE];
    int status = 0;
    print("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");
     while (1) {   
        print_prompt(status);
        process_entry(buffer);
        execute_prompt(buffer, &status);
    }
    return 0;
}
``` 
