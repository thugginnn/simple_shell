#include "my_shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in the PATH directories
 * @shell_info: a pointer to the shell's information
 * Return: 0 if success, an error code otherwise
 */
int find_program(shell_info_t *shell_info)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!shell_info->command_name)
		return (2);

	/* If it's a full_path or an executable in the same path */
	if (shell_info->command_name[0] == '/' || shell_info->command_name[0] == '.')
		return (check_file(shell_info->command_name));

	free(shell_info->tokens[0]);
	shell_info->tokens[0] = custom_str_concat(custom_str_duplicate("/"),
			shell_info->command_name);

	if (!shell_info->tokens[0])
		return (2);

	directories = tokenize_path(shell_info); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		/* Appends the function_name to the path */
		directories[i] = custom_str_concat(directories[i], shell_info->tokens[0]);
		ret_code = check_file(directories[i]);

		if (ret_code == 0 || ret_code == 126)
		{
			/* The file was found, is not a directory, and has execute permissions */
			errno = 0;
			free(shell_info->tokens[0]);
			shell_info->tokens[0] = custom_str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}

	free(shell_info->tokens[0]);
	shell_info->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the PATH variable into directories
 * @shell_info: a pointer to the shell's information
 * Return: an array of path directories
 */
char **tokenize_path(shell_info_t *shell_info)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Get the PATH value */
	PATH = shell_info_get_env_key("PATH", shell_info);

	if (!PATH || PATH[0] == '\0')
	{
		/* PATH not found or empty */
		return (NULL);
	}

	PATH = custom_str_duplicate(PATH);

	/* Find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* Reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/* Tokenize and duplicate each token of PATH */
	i = 0;
	tokens[i] = custom_str_duplicate(custom_strtok(PATH, ":"));

	while (tokens[i++])
	{
		tokens[i] = custom_str_duplicate(custom_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check_file - checks if a file exists, if it is not a directory, and
 * if it has execution permissions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or an error code if
 * it doesn't exist or doesn't meet the criteria.
 */
int check_file(char *full_path)
{
	struct stat st;

	if (stat(full_path, &st) != -1)
	{
		if (S_ISDIR(st.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}

		return (0);
	}

	/* If the file does not exist */
	errno = 127;
	return (127);
}

