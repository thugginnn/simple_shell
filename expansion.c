#include "my_shell.h"
/**
 * expand_variables - Expand variables in the input line.
 * @shell_info: A pointer to the shell's information.
 */
void expand_variables(shell_info_t *shell_info)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (shell_info->input_line == NULL)
		return;
	custom_buffer_add(line, shell_info->input_line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			custom_buffer_add(line, expansion);
			custom_buffer_add(line, shell_info->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			custom_buffer_add(line, expansion);
			custom_buffer_add(line, shell_info->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = shell_info_get_env_key(expansion, shell_info);
			line[i] = '\0';
			expansion[0] = '\0';
			custom_buffer_add(expansion, line + i + j);
			temp ? custom_buffer_add(line, temp) : 1;
			custom_buffer_add(line, expansion);
		}
	}
	if (!custom_str_compare(shell_info->input_line, line, 0))
	{
		free(shell_info->input_line);
		shell_info->input_line = custom_str_duplicate(line);
	}
}
/**
 * expand_aliases - Expand aliases in the input line.
 * @shell_info: A pointer to the shell's information.
 */
void expand_aliases(shell_info_t *shell_info)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (shell_info->input_line == NULL)
		return;
	custom_buffer_add(line, shell_info->input_line);
	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';
		temp = custom_get_alias(shell_info, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			custom_buffer_add(expansion, line + i + j);
			line[i] = '\0';
			custom_buffer_add(line, temp);
			line[custom_str_len(line)] = '\0';
			custom_buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(shell_info->input_line);
		shell_info->input_line = custom_str_duplicate(line);
	}
}
/**
 * custom_buffer_add - Append a string at the end of the buffer.
 * @buffer: The buffer to be filled.
 * @str_to_add: The string to be copied into the buffer.
 * Return: The new length of the buffer.
 */
int custom_buffer_add(char *buffer, char *str_to_add)
{
	int length, i;

	length = custom_str_len(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
