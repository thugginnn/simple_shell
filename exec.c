#include "my_shell.h"
/**
 * execute_command - Execute a command with its full path variables.
 * @shell_info: A pointer to the shell's information.
 * Return: If successful, returns zero. Otherwise, returns -1.
 */
int execute_command(shell_info_t *shell_info)
{
	int retval = 0, status;
	pid_t pid;

	retval = execute_command(shell_info);
	if (retval != -1)
	{
		return (retval);
	}
	retval = find_program(shell_info);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			retval = execve(shell_info->tokens[0],
					shell_info->tokens, shell_info->env);
			if (retval == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				errno = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				errno = 128 + WTERMSIG(status);
			}
		}
	}
	return (0);
}
