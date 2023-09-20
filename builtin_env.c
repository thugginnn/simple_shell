#include "my_shell.h"

/**
 * custom_builtin_env - Display the shell's environment.
 * @shell_info: Shell information structure.
 *
 * Return: 0 on success, or an error code on failure.
 */
int custom_builtin_env(shell_info_t *shell_info)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* If no arguments */
	if (shell_info->tokens[1] == NULL)
		print_environ(shell_info);
	else
	{
		for (i = 0; shell_info->tokens[1][i]; i++)
		{
			/* Check if there is a '=' character */
			if (shell_info->tokens[1][i] == '=')
			{
				/* Temporarily change the value of an existing variable */
				var_copy = shell_info_get_env_key(cpname, shell_info);
				if (var_copy != NULL)
					shell_info_set_env_key(cpname, shell_info->tokens[1] + i + 1, shell_info);
				/* Print the environment */
				print_environ(shell_info);
				if (shell_info_get_env_key(cpname, shell_info) == NULL)
				{
					/* Print the variable if it does not exist in the environment */
					print_to_stdout(shell_info->tokens[1]);
					print_to_stdout("\n");
				}
				else
				{
					/* Restore the old value of the variable */
					shell_info_set_env_key(cpname, var_copy, shell_info);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = shell_info->tokens[1][i];
		}
		errno = INVALID;
		perror(shell_info->command_name);
		return (1);
	}
	return (0);
}
/**
 * custom_builtin_set_env - Set or update an environment variable.
 * @shell_info: Shell information structure.
 *
 * Return: 0 on success, or an error code on failure.
 */
int custom_builtin_set_env(shell_info_t *shell_info)
{
	/* Validate arguments */
	if (shell_info->tokens[1] == NULL || shell_info->tokens[2] == NULL)
	{
		/* Custom error message */
		errno = INV;
		perror(shell_info->command_name);
		return (1);
	}
	if (shell_info->tokens[3] != NULL)
	{
		/* Custom error message */
		errno = ECK;
		perror(shell_info->command_name);
		return (1);
	}

	/* Set or update the environment variable */
	shell_info_set_env_key(shell_info->tokens[1], shell_info->tokens[2], shell_info);
	return (0);
}
/**
 * custom_builtin_unset_env - Unset an environment variable.
 * @shell_info: Shell information structure.
 *
 * Return: 0 on success, or an error code on failure.
 */
int custom_builtin_unset_env(shell_info_t *shell_info)
{
	/* Validate arguments */
	if (shell_info->tokens[1] == NULL)
	{
		/* Custom error message */
		errno = ARG;
		perror(shell_info->command_name);
		return (1);
	}
	if (shell_info->tokens[2] != NULL)
	{
		/* Custom error message */
		errno = FOR;
		perror(shell_info->command_name);
		return (1);
	}

	/* Unset the environment variable */
	shell_info_remove_env_key(shell_info->tokens[1], shell_info);
	return (0);
}
