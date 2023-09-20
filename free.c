#include "my_shell.h"

/**
 * free_array_of_pointers - this would free each pointer of an array of
 * pointer and the array itself.
 * @array: The array of pointers.
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
		free(array[i]);

		free(array);
	}
}

/**
 * free_recurrent_info - this Frees the fields that need
 * to be freed in each loop.
 * @shell_info: A pointer to the shell's information.
 */
void free_recurrent_info(shell_info_t *shell_info)
{
	if (shell_info->tokens)
		free_array_of_pointers(shell_info->tokens);
	if (shell_info->input_line)
		free(shell_info->input_line);
	if (shell_info->command_name)
		free(shell_info->command_name);

	shell_info->input_line = NULL;
	shell_info->command_name = NULL;
	shell_info->tokens = NULL;
}

/**
 * free_all_info - this Frees all fields of the shell's information.
 * @shell_info: A pointer to the shell's information.
 */
void free_all_info(shell_info_t *shell_info)
{
	if (shell_info->file_descriptor != 0)
	{
		if (close(shell_info->file_descriptor))
			perror("Error closing file descriptor");
	}
	free_recurrent_info(shell_info);
	free_array_of_pointers(shell_info->env);
	free_array_of_pointers(shell_info->alias_list);
}
