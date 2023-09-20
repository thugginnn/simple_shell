#include "my_shell.h"

/**
 * main - this Initializes the shell and starts the main loop.
 * @argc: Number of arguments received from the command line.
 * @argv: Array of arguments received from the command line.
 * @env: Array of environment variables.
 * Return: Always returns 0.
 */
int main(int argc, char *argv[], char *env[])
{
	shell_info_t shell_info_struct = {NULL}, *shell_info = &shell_info_struct;
	char *prompt = "";

	initialize_shell_info(shell_info, argc, argv, env);

	signal(SIGINT, handle_ctrl_cc);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
	errno = 2; /* Nothing  inputed  , assume interactive mode */
	prompt = PROMPT_MSG;
	}
	errno = 0;
	loop_main(prompt, shell_info);
	return (0);
}

/**
 * handle_ctrl_cc - This Handles the SIGINT (Ctrl+C) signal.
 * @UNUSED: Unused parameter.
 *
 */
void handle_ctrl_cc(int opr UNUSED)
{
	print_to_stdout("\n");
	print_to_stdout(PROMPT_MSG);
}

/**
 * initialize_shell_info - Initializes the shell_info structure.
 * @shell_info: Pointer to the shell_info structure.
 * @argc: Number of arguments received from the command line.
 * @argv: Array of arguments received from the command line.
 * @env: Array of environment variables.
 */
void initialize_shell_info(shell_info_t *shell_info, int argc,
char *argv[], char **env)
{
	int i = 0;

	shell_info->program_name = argv[0];
	shell_info->input_line = NULL;
	shell_info->command_name = NULL;
	shell_info->exec_counter = 0;

	if (argc == 1)
		shell_info->file_descriptor = STDIN_FILENO;
	else
	{
		shell_info->file_descriptor = open(argv[1], O_RDONLY);
		if (shell_info->file_descriptor == -1)
		{
			print_to_stderr(shell_info->program_name);
			print_to_stderr(": 0: unable to open ");
			print_to_stderr(argv[1]);
			print_to_stderr("\n");
			exit(127);
		}
	}

	shell_info->tokens = NULL;
	shell_info->env = malloc(sizeof(char *) * 50);

	if (env)
	{
		for (; env[i]; i++)
		{
			shell_info->env[i] = custom_str_duplicate(env[i]);
		}
	}
	shell_info->env[i] = NULL;
	env = shell_info->env;

	shell_info->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		shell_info->alias_list[i] = NULL;
	}
}

/**
 * loop_main - Main loop for the shell, continuously prompts for * input and
 * processes commands.
 * @prompt: The prompt message to be printed.
 * @shell_info: Pointer to the shell_info structure.
 */
void loop_main(char *prompt, shell_info_t *shell_info)
{
	int error_code = 0, string_len = 0;

	while (++(shell_info->exec_counter))
	{
		print_to_stdout(prompt);
		error_code = string_len = custom_getline(shell_info);

		if (error_code == EOF)
	{
		free_all_info(shell_info);
		exit(errno);
	}
	if (string_len >= 1)
	{
		expand_aliases(shell_info);
		expand_variables(shell_info);
		custom_tokenize(shell_info);
		if (shell_info->tokens[0])
		{
			error_code = execute_command(shell_info);
			if (error_code != 0)
				print_error_message(error_code, shell_info);
		}
		free_recurrent_info(shell_info);
	}
	}
}
