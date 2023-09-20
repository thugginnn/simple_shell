#include "my_shell.h"

/**
 * print_to_stdout - this Writes a string to standard output.
 * @string: Pointer to the string to be written.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_to_stdout(char *string)
{
	return (write(STDOUT_FILENO, string, custom_str_len(string)));
}

/**
 * print_to_stderr - Writes a string to standard error.
 * @string: Pointer to the string to be written.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_to_stderr(char *string)
{
	return (write(STDERR_FILENO, string, custom_str_len(string)));
}

/**
 * print_error_message - Prints an error message to standard error.
 * @error_code: The error code to print.
 * @shell_info: Pointer to the shell information.
 * Return: 0 on success, -1 on failure.
 */
int print_error_message(int error_code, shell_info_t *shell_info)
{
	char exec_counter_str[10] = {'\0'};

	long_to_string((long) shell_info->exec_counter, exec_counter_str, 10);

	if (error_code == 2 || error_code == 3)
	{
		print_to_stderr(shell_info->program_name);
		print_to_stderr(": Error: ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(shell_info->tokens[0]);
		if (error_code == 2)
			print_to_stderr(": Invalid number: ");
		else
			print_to_stderr(": No such directory: ");
		print_to_stderr(shell_info->tokens[1]);
		print_to_stderr("\n");
	}
	else if (error_code == 127)
	{
		print_to_stderr(shell_info->program_name);
		print_to_stderr(": Error: ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(shell_info->command_name);
		print_to_stderr(": Command not found\n");
	}
	else if (error_code == 126)
	{
		print_to_stderr(shell_info->program_name);
		print_to_stderr(": Error: ");
		print_to_stderr(exec_counter_str);
		print_to_stderr(shell_info->command_name);
		print_to_stderr(": Access denied\n");
	}

	return (0);
}
