#include "my_shell.h"

/**
 * custom_builtins_list - Search for a match and
 * execute the associated builtin.
 * @shell_info: Shell information structure.
 *
 * Return: Returns the return value of the
 * executed function if there is a match,
 *         otherwise returns -1.
 **/
int custom_builtins_list(shell_info_t *shell_info)
{
	int iterator;
	cmd_builtins options[] =
	{
		{"exit", custom_builtin_exit},
		{"help", custom_builtin_help},
		{"cd", custom_builtin_cd},
		{"alias", custom_builtin_alias},
		{"env", custom_builtin_env},
		{"setenv", custom_builtin_set_env},
		{"unsetenv", custom_builtin_unset_env},
		{NULL, NULL}
	};

	/* Walk through the structure */
	for (iterator = 0; options[iterator].cmd_builtin != NULL; iterator++)
	{
		/* If there is a match between the given command and a builtin, */
		if (custom_str_compare(options[iterator].cmd_builtin,
					shell_info->command_name, 0))
		{
			/* Execute the function and return its return value */
			return (options[iterator].function(shell_info));
		}
	}

	/* If there is no match, return -1 */
	return (-1);
}

