#include "my_shell.h"

/**
 * custom_builtin_exit - Exit the shell with a status code.
 * @shell_info: Shell information structure.
 * Return: 0 if successful, or an error code if there's an issue.
 */
int custom_builtin_exit(shell_info_t *shell_info)
{
    int i;
    if (shell_info->tokens[1] != NULL)
    { /* if there's an argument for exit, check if it's a number */
        for (i = 0; shell_info->tokens[1][i]; i++)
        {
            if ((shell_info->tokens[1][i] < '0' || shell_info->tokens[1][i] > '9') && shell_info->tokens[1][i] != '+')
            {
                /* if it's not a number */
                errno = 2;
                return 2;
            }
        }
        errno = atoi_custom(shell_info->tokens[1]);
    }
    free_all_info(shell_info);
    exit(errno);

}

/**
 * custom_builtin_cd - Change the current working directory.
 * @shell_info: Shell information structure.
 * Return: 0 if successful, or an error code if there's an issue.
 */
int custom_builtin_cd(shell_info_t *shell_info)
{
	char *dir_home = shell_info_get_env_key("HOME", shell_info);
	char *dir_old = NULL;
	char old_dir[128] = {0};

	if (shell_info->tokens[1])
	{
		if (custom_str_compare(shell_info->tokens[1], "-", 0))
		{
			dir_old = shell_info_get_env_key("OLDPWD", shell_info);
			if (dir_old)
			{
				int error_code = custom_set_work_directory(shell_info, dir_old);

				print_to_stdout(shell_info_get_env_key("PWD", shell_info));
				print_to_stdout("\n");
				return (error_code);
			}
			print_to_stdout(shell_info_get_env_key("PWD", shell_info));
			print_to_stdout("\n");
			return (0);
		}
		else
		{
			return (custom_set_work_directory(shell_info, shell_info->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);
		return (custom_set_work_directory(shell_info, dir_home));
	}

	return (0);
}

/**
 * custom_set_work_directory - Set the working directory.
 * @shell_info: Shell information structure.
 * @new_dir: Path to be set as the working directory.
 * Return: 0 if successful, or an error code if there's an issue.
 */
int custom_set_work_directory(shell_info_t *shell_info, char *new_dir)
{
	char old_dir[128] = {0};
	int error_code = 0;

	getcwd(old_dir, 128);
	if (!custom_str_compare(old_dir, new_dir, 0))
	{
		error_code = chdir(new_dir);
		if (error_code == -1)
		{
			errno = 2;
			return (3);
		}
		shell_info_set_env_key("PWD", new_dir, shell_info);
	}

	shell_info_set_env_key("OLDPWD", old_dir, shell_info);
	return (0);
}

/**
 * custom_builtin_help - Display help messages for built-in commands.
 * @shell_info: Shell information structure.
 * Return: 0 if successful, or an error code if there's an issue.
 */
int custom_builtin_help(shell_info_t *shell_info)
{
	int i, length = 0;
	char *messages[] = {
		"HELP_MSG: This is the general help message.",
		"HELP_EXIT_MSG: Help message for the exit command.",
		"HELP_ENV_MSG: Help message for the env command.",
		"HELP_SETENV_MSG: Help message for the setenv command.",
		"HELP_UNSETENV_MSG: Help message for the unsetenv command.",
		"HELP_CD_MSG: Help message for the cd command."
	};

	if (shell_info->tokens[1] == NULL)
	{
		print_to_stdout(messages[0] + 6);
		return (1);
	}

	if (shell_info->tokens[2] != NULL)
	{
		errno = ECH;
		perror(shell_info->command_name);
		return (5);
	}

	for (i = 1; i < 6; i++)
	{
		length = custom_str_len(shell_info->tokens[1]);
		if (custom_str_compare(shell_info->tokens[1], messages[i], length))
		{
			print_to_stdout(messages[i] + length + 1);
			return (1);
		}
	}
	errno = INV;
	perror(shell_info->command_name);
	return (0);
}

/**
 * custom_builtin_alias - Add, remove, or show aliases.
 * @shell_info: Shell information structure.
 * Return: 0 if successful, or an error code if there's an issue.
 */
int custom_builtin_alias(shell_info_t *shell_info)
{
	int i = 0;

	/* If there are no arguments, print all aliases */
	if (shell_info->tokens[1] == NULL)
		return (custom_print_alias(shell_info, NULL));

	while (shell_info->tokens[++i])
	{
		/* If there are arguments, set or print each alias */
		if (count_characters(shell_info->tokens[i], "="))
			custom_set_alias(shell_info->tokens[i], shell_info);
		else
			custom_print_alias(shell_info, shell_info->tokens[i]);
	}

	return (0);
}

