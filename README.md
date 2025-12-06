
-----

# EnseaSH - Micro Shell Project

## 📜 Description

[cite_start]**EnseaSH** is a micro shell developed as a synthesis practical work ("TP de Synthèse") for the 2nd year of the Computer Science Major at **ENSEA**[cite: 2, 5].

The goal of this project is to understand the low-level mechanisms of a shell, including process creation, signal handling, and file descriptor management. [cite_start]This shell executes commands, displays their exit codes/signals, and measures their execution time[cite: 9, 25].

[cite_start]**Course:** 2nd Year / Computer Science Major [cite: 5]
[cite_start]**Authors:** [Agheles Mekdache] & [Salim Bouateli] [cite: 12]

## 🚀 Features

[cite_start]The shell implements the following functionalities, developed incrementally[cite: 26]:

1.  [cite_start]**Welcome Message**: Displays a welcome message and a prompt (`enseash %`) upon startup[cite: 27].
2.  **Command Execution**:
      * [cite_start]Supports simple commands (e.g., `ls`, `date`)[cite: 34].
      * [cite_start]Supports complex commands with arguments (e.g., `ls -l /tmp`)[cite: 56].
3.  [cite_start]**REPL (Read-Eval-Print Loop)**: Reads user input, executes it, and waits for the next command[cite: 32].
4.  [cite_start]**Exit Management**: Cleanly exits the shell using the `exit` command or `<Ctrl>+d`[cite: 41].
5.  [cite_start]**Status Display**: Shows the exit code or signal of the previous command in the prompt (e.g., `[exit:0]` or `[sign:9]`)[cite: 46].
6.  [cite_start]**Execution Time**: Measures and displays the execution time of commands using `clock_gettime` (e.g., `[exit:0|10ms]`)[cite: 50].
7.  **Redirections**:
      * [cite_start]Input redirection (`<`)[cite: 63].
      * [cite_start]Output redirection (`>`)[cite: 63].
8.  [cite_start]**Pipes**: Supports piping between two commands (e.g., `ls | wc -l`)[cite: 67].
9.  [cite_start]**Background Processes (Bonus)**: Supports executing commands in the background using `&`[cite: 71].

## 🛠 Technical Constraints

In accordance with the project guidelines:

  * [cite_start]**No `printf`**: Standard I/O functions like `printf` are avoided in favor of `write` for better compatibility with low-level operations[cite: 19].
  * **No `system()`**: The `system` function is strictly forbidden; [cite_start]`exec` family functions are used instead[cite: 21].
  * [cite_start]**Code Quality**: No "magic numbers," clean variable naming in English, and modular function design[cite: 16, 17, 18].
  * [cite_start]**String Manipulation**: Usage of `string.h` and safe functions like `strn...`[cite: 20].

## 📦 Installation & Usage

### 1\. Clone the repository

```bash
git clone https://github.com/zeroxy21/enseash.git
cd enseash
```

### 2\. Compile

To compile the project, use the provided Makefile (or gcc directly):

```bash
gcc -o enseash main.c # Add other source files if necessary
```

*(Note: If you have a Makefile, advise the user to simply run `make`)*

### 3\. Run

Start the shell:

```bash
./enseash
```

### 4\. Examples

```bash
$ ./enseash
Bienvenue dans le Shell ENSEA.
Pour quitter, tapez 'exit'.

enseash % date
Sun Dec 13 13:19:40 CET 2020

enseash [exit:0|1ms] % unknown_command
Command not found

enseash [exit:127|0ms] % sleep 2
(Waits for 2 seconds)

enseash [exit:0|2000ms] % exit
Bye bye...
```

## 📋 Project Status

  * [x] Basic Prompt & Welcome Message
  * [x] Simple Command Execution
  * [x] Display Exit Code/Signals
  * [x] Execution Timing
  * [x] Complex Commands (Arguments)
  * [x] Redirections (\<, \>)
  * [x] Pipes (|)
  * [ ] Background Execution (&) *(Cochez cette case si vous avez fini la partie 9)*

-----

[cite_start]*Based on the "Ensea in the Shell" assignment by C. Barès & N. Papazoglou[cite: 8].*

-----
