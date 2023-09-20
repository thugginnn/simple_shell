#include "my_shell.h"

/**
 * custom_getline - Read one line from the prompt.
 * @shell_info: Structure containing shell-related data.
 *
 * This function reads a line from the provided file descriptor and splits it
 * into separate commands, considering logical operators '&&' and '||'.
 *
 * Return: Number of bytes read, or -1 on EOF/error.
 */
int custom_getline(shell_info_t *shell_info)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands[10] = {NULL};
	static char operators[10] = {'\0'};
	ssize_t bytes_read;
	size_t i = 0;

	/* Check if there are no more commands in the array */
	/* and check the logical operators */
	if (!commands[0] || (operators[0] == '&' && errno != 0) ||
	    (operators[0] == '|' && errno == 0))
	{
		/* Free the memory allocated in the array if it exists */
		for (i = 0; commands[i]; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}

		/* Read from the file descriptor into buff */
		bytes_read = read(shell_info->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* Split lines by '\n' or ';' */
		i = 0;
		do {
			commands[i] = custom_str_duplicate(custom_strtok(i ? NULL : buff, "\n;"));
			/* Check and split for '&&' and '||' operators */
			i = custom_check_logic_ops(commands, i, operators);
		} while (commands[i++]);
	}

	/* Obtain the next command (command 0) and remove it from the array */
	shell_info->input_line = commands[0];
	for (i = 0; commands[i]; i++)
	{
		commands[i] = commands[i + 1];
		operators[i] = operators[i + 1];
	}
	return (custom_str_len(shell_info->input_line));
}

/**
 * custom_check_logic_ops - Check and split for '&&' and '||' operators.
 * @commands: Array of commands.
 * @i: Index in the commands array to be checked.
 * @operators: Array of logical operators for each previous command.
 *
 * This function scans a command for '&&' and '||' operators and splits the
 * command accordingly, updating the commands array.
 *
 * Return: Index of the last command in the commands array.
 */
int custom_check_logic_ops(char *commands[], int i, char operators[])
{
	char *temp = NULL;
	int j;

	/* Check for the '&' character in the command line */
	for (j = 0; commands[i] != NULL && commands[i][j]; j++)
	{
		if (commands[i][j] == '&' && commands[i][j + 1] == '&')
		{
			/* Split the line when '&&' is found */
			temp = commands[i];
			commands[i][j] = '\0';
			commands[i] = custom_str_duplicate(commands[i]);
			commands[i + 1] = custom_str_duplicate(temp + j + 2);
			i++;
			operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands[i][j] == '|' && commands[i][j + 1] == '|')
		{
			/* Split the line when '||' is found */
			temp = commands[i];
			commands[i][j] = '\0';
			commands[i] = custom_str_duplicate(commands[i]);
			commands[i + 1] = custom_str_duplicate(temp + j + 2);
			i++;
			operators[i] = '|';
			free(temp);
			j = 0;
		}
	}

	return (i);
}

