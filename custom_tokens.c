#include "my_shell.h"

/**
 * custom_tokenize - Tokenizes the input string using specified delimiters.
 * @shell_info: A pointer to the shell's information.
 * Return: An array of tokenized strings.
 */
void custom_tokenize(shell_info_t *shell_info)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = custom_str_len(shell_info->input_line);
	if (length)
	{
		if (shell_info->input_line[length - 1] == '\n')
			shell_info->input_line[length - 1] = '\0';
	}

	for (i = 0; shell_info->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
	{
		if (shell_info->input_line[i] == delimiter[j])
			counter++;
	}
	}

	shell_info->tokens = malloc(counter * sizeof(char *));
	
	if (shell_info->tokens == NULL)
	{
		perror(shell_info->program_name);
		exit(errno);
	}
	i = 0;
	shell_info->tokens[i] = custom_str_duplicate
		(custom_strtok(shell_info->input_line, delimiter));
	shell_info->command_name = custom_str_duplicate(shell_info->tokens[0]);
	while (shell_info->tokens[i++])
	{
		shell_info->tokens[i] = custom_str_duplicate(custom_strtok(NULL, delimiter));
	}
}
