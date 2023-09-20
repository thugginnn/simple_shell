#include "my_shell.h"

/**
 * custom_print_alias - Display aliases.
 * @shell_info: Shell information structure.
 * @alias: Name of the alias to be displayed.
 *
 * Return: 0 on success, or other value for errors.
 */
int custom_print_alias(shell_info_t *shell_info, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (shell_info->alias_list)
	{
		alias_length = custom_str_len(alias);
		for (i = 0; shell_info->alias_list[i]; i++)
		{
			if (!alias || (custom_str_compare(shell_info->alias_list[i],
						alias, alias_length) && shell_info->alias_list[i][alias_length] == '='))
			{
				for (j = 0; shell_info->alias_list[i][j]; j++)
				{
					buffer[j] = shell_info->alias_list[i][j];
					if (shell_info->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				custom_buffer_add(buffer, "'");
				custom_buffer_add(buffer, shell_info->alias_list[i] + j + 1);
				custom_buffer_add(buffer, "'\n");
				print_to_stdout(buffer);
			}
		}
	}
	return (0);
}

/**
 * custom_get_alias - Retrieve an alias value.
 * @shell_info: Shell information structure.
 * @name: Name of the requested alias.
 *
 * Return: The alias value if found, or NULL if not found.
 */
char *custom_get_alias(shell_info_t *shell_info, char *name)
{
	int i, alias_length;

	/* Validate the arguments */
	if (name == NULL || shell_info->alias_list == NULL)
		return (NULL);

	alias_length = custom_str_len(name);

	for (i = 0; shell_info->alias_list[i]; i++)
	{
		/* Iterate through the alias list and check for a matching name */
		if (custom_str_compare(name, shell_info->alias_list[i], alias_length) &&
			shell_info->alias_list[i][alias_length] == '=')
		{
			/* Return the value of the alias when found */
			return (shell_info->alias_list[i] + alias_length + 1);
		}
	}
	/* Return NULL if the alias was not found */
	return (NULL);
}
/**
 * custom_set_alias - Add or override an alias.
 * @alias_string: Alias to be set in the form (name='value').
 * @shell_info: Shell information structure.
 *
 * Return: 0 on success, or 1 for errors.
 */
int custom_set_alias(char *alias_string, shell_info_t *shell_info)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* Validate the arguments */
	if (alias_string == NULL || shell_info->alias_list == NULL)
		return (1);

	/* Iterate through the alias string to find the '=' character */
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/* Check if the value of the alias is another alias */
			temp = custom_get_alias(shell_info, alias_string + i + 1);
			break;
		}
	}
	/* Iterate through the alias list and check for a matching name */
	for (j = 0; shell_info->alias_list[j]; j++)
	{
		if (custom_str_compare(buffer, shell_info->alias_list[j], i) &&
			shell_info->alias_list[j][i] == '=')
		{
			free(shell_info->alias_list[j]);
			break;
		}
	}
	if (temp)
	{
		custom_buffer_add(buffer, "=");
		custom_buffer_add(buffer, temp);
		shell_info->alias_list[j] = custom_str_duplicate(buffer);
	}
	else
	{
		shell_info->alias_list[j] = custom_str_duplicate(alias_string);
	}
	return (0);
}
