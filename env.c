#include "my_shell.h"

/**
 * shell_info_get_env_key - Get the value of an environment variable.
 * @key: The environment variable of interest.
 * @shell_info: Shell information structure.
 *
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */
char *shell_info_get_env_key(char *key, shell_info_t *shell_info)
{
	int i, key_length = 0;

	/* Validate the arguments */
	if (key == NULL || shell_info->env == NULL)
		return (NULL);

	/* Obtain the length of the variable requested */
	key_length = custom_str_len(key);

	for (i = 0; shell_info->env[i]; i++)
	{
		/* Iterate through the environment and check for coincidence of the name */
		if (custom_str_compare(key, shell_info->env[i], key_length) &&
			shell_info->env[i][key_length] == '=')
		{
			/* Return the value of the key NAME= when found */
			return (shell_info->env[i] + key_length + 1);
		}
	}

	/* Return NULL if not found */
	return (NULL);
}

/**
 * shell_info_set_env_key - Overwrite the value of the environment variable
 * or create it if it does not exist.
 * @key: Name of the variable to set.
 * @value: New value.
 * @shell_info: Shell information structure.
 *
 * Return: 1 if the parameters are NULL, 2
 * if there is an error, or 0 if success.
 */
int shell_info_set_env_key(char *key, char *value, shell_info_t *shell_info)
{
	int i, key_length = 0, is_new_key = 1;

	/* Validate the arguments */
	if (key == NULL || value == NULL || shell_info->env == NULL)
		return (1);

	/* Obtain the length of the variable requested */
	key_length = custom_str_len(key);

	for (i = 0; shell_info->env[i]; i++)
	{
		/* Iterate through the environment and check for coincidence of the name */
		if (custom_str_compare(key, shell_info->env[i], key_length) &&
			shell_info->env[i][key_length] == '=')
		{
			/* If the key already exists, free the entire variable */
			is_new_key = 0;
			free(shell_info->env[i]);
			break;
		}
	}

	/* Create a string of the form key=value */
	shell_info->env[i] = custom_str_concat(custom_str_duplicate(key), "=");
	shell_info->env[i] = custom_str_concat(shell_info->env[i], value);

	if (is_new_key)
	{
		/* If the variable is new, create it at the end of the list and set NULL */
		shell_info->env[i + 1] = NULL;
	}

	return (0);
}

/**
 * shell_info_remove_env_key - Remove a key from the environment.
 * @key: The key to remove.
 * @shell_info: Shell information structure.
 *
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int shell_info_remove_env_key(char *key, shell_info_t *shell_info)
{
	int i, key_length = 0;

	/* Validate the arguments */
	if (key == NULL || shell_info->env == NULL)
		return (0);

	/* Obtain the length of the variable requested */
	key_length = custom_str_len(key);

	for (i = 0; shell_info->env[i]; i++)
	{
		/* Iterate through the environment and check for coincidences */
		if (custom_str_compare(key, shell_info->env[i], key_length) &&
			shell_info->env[i][key_length] == '=')
		{
			/* If the key already exists, remove it */
			free(shell_info->env[i]);

			/* Move the other keys one position down */
			i++;
			for (; shell_info->env[i]; i++)
			{
				shell_info->env[i - 1] = shell_info->env[i];
			}

			/* Set the NULL value at the new end of the list */
			shell_info->env[i - 1] = NULL;
			return (1);
		}
	}

	return (0);
}

/**
 * print_environ - Prints the current environment.
 * @shell_info: Shell information structure.
 *
 * Return: Nothing.
 */
void print_environ(shell_info_t *shell_info)
{
	int j;

	for (j = 0; shell_info->env[j]; j++)
	{
		print_to_stdout(shell_info->env[j]);
		print_to_stdout("\n");
	}
}

