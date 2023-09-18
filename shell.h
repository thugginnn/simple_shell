#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct shell_info - struct for the shell's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read by _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor for input commands
 * @tokens: pointer to an array of tokenized input
 * @env: copy of the environment variables
 * @alias_list: array of pointers with aliases.
 */
typedef struct shell_info
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} shell_info_t;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(shell_info_t *shell_info);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Initialize the struct with the info of the program */
void initialize_shell_info(shell_info_t *shell_info, int argc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void loop_main(char *prompt, shell_info_t *shell_info);

/* Print the prompt in a new line */
void handle_ctrl_cc(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standard input */
int custom_getline(shell_info_t *shell_info);

/* Split the input into commands separated by logical operators */
int custom_check_logic_ops(char *commands[], int i, char operators[]);


/*======== expansions.c ========*/

/* Expand variables */
void expand_variables(shell_info_t *shell_info);

/* Expand aliases */
void expand_aliases(shell_info_t *shell_info);

/* Append the string to the end of the buffer */
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string into tokens using a designated delimiter */
void custom_tokenize(shell_info_t *shell_info);

/* Create a pointer to a part of a string */
char *custom_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute_command(shell_info_t *shell_info);


/*======== builtins_list.c ========*/

/* If matched with a builtin, execute it */
int custom_builtins_list(shell_info_t *shell_info);


/*======== find_in_path.c ========*/

/* Create an array of the path directories */
char **tokenize_path(shell_info_t *shell_info);

/* Search for a program in the PATH */
int find_program(shell_info_t *shell_info);

/* checks if the file exist */
int check_file(char *full_path);

/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed for each loop */
void free_recurrent_info(shell_info_t *shell_info);

/* Free all fields of the shell_info */
void free_all_info(shell_info_t *shell_info);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int custom_builtin_exit(shell_info_t *shell_info);

/* Change the current directory */
int custom_builtin_cd(shell_info_t *shell_info);

/* Set the working directory */
int custom_set_work_directory(shell_info_t *shell_info, char *new_dir);

/* Show help information */
int custom_builtin_help(shell_info_t *shell_info);

/* Set, unset, and show aliases */
int custom_builtin_alias(shell_info_t *shell_info);


/*======== builtins_env.c ========*/

/* Show the environment where the shell runs */
int custom_builtin_env(shell_info_t *shell_info);

/* Create or override an environment variable */
int custom_builtin_set_env(shell_info_t *shell_info);

/* Delete an environment variable */
int custom_builtin_unset_env(shell_info_t *shell_info);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Get the value of an environment

 variable */
char *shell_info_get_env_key(char *name, shell_info_t *shell_info);

/* this Overwrite the value of the environment variable */
int shell_info_set_env_key(char *key, char *value, shell_info_t *shell_info);

/* this Remove a key from the environment */
int shell_info_remove_env_key(char *key, shell_info_t *shell_info);

/* this Print the current environ */
void print_environ(shell_info_t *shell_info);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* this print a string to standard output */
int print_to_stdout(char *string);

/* this print a string to standard error */
int print_to_stderr(char *string);

/*this print an error message with the provided error code and info */
int print_error_message(int errorcode, shell_info_t *shell_info);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* this Count the number of characters in a string */
int custom_str_len(char *string);

/* this  Duplicate a string */
char *custom_str_duplicate(char *string);

/* this Compare two strings */
int custom_str_compare(char *string1, char *string2, int number);

/* this Concatenate two strings */
char *custom_str_concat(char *string1, char *string2);

/*  this Reverse a string */
void custom_str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Convert from int to string */
void long_to_string(long number, char *string, int base);

/* Convert a string to a number */
int atoi_custom(char *s);

/* Count the occurrences of a character in a string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* This Print the list of aliases */
int custom_print_alias(shell_info_t *shell_info, char *alias);

/* this Get the alias name */
char *custom_get_alias(shell_info_t *shell_info, char *alias);

/* this  Set the alias name */
int custom_set_alias(char *alias_string, shell_info_t *shell_info);


#endif /* SHELL_H */
