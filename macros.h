#ifndef MACROSS_H
#define MACROSS_H

/* this is the Prompt to be printed */
#define PROMPT_MSG "$ custom_shell> "

/* the unused attribute */
#define UNUSED __attribute__((unused))

/* thiis is Buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* this are formatted string FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [directory]\n\n"\
"	this Changes the shell's working directory.\n\n"\
"	If no argument is given to cd, the command will be interpreted\n"\
"	as cd $HOME or the path .\n"\
"	If the argument is '-', the command will be interpreted\n"\
"	as cd $OLDPWD or the path.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	This Exit the custom shell.\n\n"\
"	Exits the shell with a status of N. If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	This Print environment variables.\n\n"\
"	The env command when pressed will print a complete list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	This will Change or add an environment variable.\n\n"\
"	This will Initialize a new environment variable or modify an existing one.\n"\
"	When there are not the correct number of arguments, an error message is printed.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function would delete a variable from the environment.\n\n"\
"	would display an error message if the correct number of arguments are not inputed .\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAMES]\n\n"\
"	This Would Display information about builtin commands.\n\n"\
"	This Displays brief summaries of builtin commands. If BUILTIN_NAME is\n"\
"	specified, it gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise, the list of help topics is printed.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifying a help topic.\n\n"\
"	cd\t[directory]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[builtin_name]\n\n"

#endif
