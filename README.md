# Simple Shell

This is an ALX collaboration project on Shell. We were tasked to create a simple shell that mimics the Bash shell. Our shell shall be called **hsh**.

## Project Completion Details

- **Programming Languages**: C, Shell
- **Documentation Style**: Betty Style Documentation

## General Requirements for the Project

- All files will be compiled on **Ubuntu 20.04 LTS** using `gcc`, with the following options: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files should end with a new line
- A **README.md** file, at the root of the project folder, is mandatory
- Use the Betty style, which will be checked using `betty-style.pl` and `betty-doc.pl`
- Ensure the shell does not have any memory leaks
- No more than 5 functions per file
- All header files should be include guarded
- Write a README with a detailed description of the project

## Description

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

### How **hsh** Works

1. Prints a prompt and waits for a command from the user
2. Creates a child process in which the command is checked
3. Checks for built-ins, aliases in the PATH, and local executable programs
4. The child process is replaced by the command, which accepts arguments
5. When the command is done, the program returns to the parent process and prints the prompt
6. The program is ready to receive a new command
7. To exit: press Ctrl-D or enter "exit" (with or without a status)
8. Works also in non-interactive mode

## Compilation

To compile the project, use the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Authors

Tolulope Olanrewaju, Paul Iyiade
