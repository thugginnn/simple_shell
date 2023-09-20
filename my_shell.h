#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdlib.h> /* For standard library functions */
#include <stddef.h> /* For NULL and other standard definitions */
#include <signal.h> /* For signal management */
#include <fcntl.h>  /* For file control options */
#include <unistd.h> /* For various POSIX functions */
#include <string.h> /* For string manipulation functions */
#include <stdio.h>  /* For standard input/output functions */
#include <sys/wait.h> /* For process wait functions */
#include <sys/types.h> /* For system data types */
#include <errno.h> /* For error codes */
#include <sys/stat.h> /* For file status information */

#define INVALID 1
#define INV 2
#define ECK 3
#define ARG 4
#define FOR 5
#define ECH 6


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
	char *command_name;
	char *input_line;
 	char *program_name;
	int file_descriptor;
	int exec_counter;
	char **env;
	char **tokens;
	char **alias_list;
} shell_info_t;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct cmd_builtins
{
    char *cmd_builtin;
    int (*function)(shell_info_t *shell_info);
} cmd_builtins;


/************* MAIN FUNCTIONS **********/

/* Initialize the struct with the info of the program */
void initialize_shell_info(shell_info_t *shell_info, int argc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void loop_main(char *prompt, shell_info_t *shell_info);

/* Print the prompt in a new line */
void handle_ctrl_cc(int opr UNUSED);


/* Read one line of the standard input */
int custom_getline(shell_info_t *shell_info);

/* Split the input into commands separated by logical operators */
int custom_check_logic_ops(char *commands[], int i, char operators[]);


/* Expand variables */
void expand_variables(shell_info_t *shell_info);

/* Expand aliases */
void expand_aliases(shell_info_t *shell_info);

/* Append the string to the end of the buffer */
int custom_buffer_add(char *buffer, char *str_to_add);


/* Separate the string into tokens using a designated delimiter */
void custom_tokenize(shell_info_t *shell_info);

/* Create a pointer to a part of a string */
char *custom_strtok(char *line, char *delim);


/* Execute a command with its entire path */
int execute_command(shell_info_t *shell_info);



/* If matched with a builtin, execute it */
int custom_builtins_list(shell_info_t *shell_info);


/* Create an array of the path directories */
char **tokenize_path(shell_info_t *shell_info);

/* Search for a program in the PATH */
int find_program(shell_info_t *shell_info);

/* checks if the file exist */
int check_file(char *full_path);


/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed for each loop */
void free_recurrent_info(shell_info_t *shell_info);

/* Free all fields of the shell_info */
void free_all_info(shell_info_t *shell_info);

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

/* Show the environment where the shell runs */
int custom_builtin_env(shell_info_t *shell_info);

/* Create or override an environment variable */
int custom_builtin_set_env(shell_info_t *shell_info);

/* Delete an environment variable */
int custom_builtin_unset_env(shell_info_t *shell_info);



/* Get the value of an environment

 variable */
char *shell_info_get_env_key(char *name, shell_info_t *shell_info);

/* this Overwrite the value of the environment variable */
int shell_info_set_env_key(char *key, char *value, shell_info_t *shell_info);

/* this Remove a key from the environment */
int shell_info_remove_env_key(char *key, shell_info_t *shell_info);

/* this Print the current environ */
void print_environ(shell_info_t *shell_info);

/* this print a string to standard output */
int print_to_stdout(char *string);

/* this print a string to standard error */
int print_to_stderr(char *string);

/*this print an error message with the provided error code and info */
int print_error_message(int error_code, shell_info_t *shell_info);


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

/* Convert from int to string */
void long_to_string(long number, char *string, int base);

/* Convert a string to a number */
int atoi_custom(char *s);

/* Count the occurrences of a character in a string */
int count_characters(char *string, char *character);


/* This Print the list of aliases */
int custom_print_alias(shell_info_t *shell_info, char *alias);

/* this Get the alias name */
char *custom_get_alias(shell_info_t *shell_info, char *alias);

/* this  Set the alias name */
int custom_set_alias(char *alias_string, shell_info_t *shell_info);


#endif /* MY_SHELL_H */
