#include "main.h"
/**
 * parse_line - Parses the command line looking for commands and argumements.
 * This function it is also in charged of freeing memory that is not longer
 * needed by the program.
 * @line: A pointer to a string. Will always be NULL upon function entry.
 * @size: A holder for numbers of size_t. Will always be initilized to 0.
 * @command_counter: A counter keeping track of how many commands have been
 * entered into the shell.
 * @av: Name of the program running the shell
 */
void parse_line(char *line, size_t size, int command_counter, char **av)
{
	int x;
	ssize_t read_ln;
	int tkn_count;
	char **param_array;
	const char *delim = "\n\t ";

	tkn_count = 0;
	write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	read_ln = getline(&line, &size, stdin);
	if (read_ln != -1)
	{
		param_array = token_interface(line, delim, tkn_count);
		if (param_array[0] == NULL)
		{
			single_free(2, param_array, line);
			return;
		}
		x = built_in(param_array, line);
		if (x == -1)
			create_child(param_array, line, command_counter, av);
		for (x = 0; param_array[x] != NULL; x++)
			free(param_array[x]);
		single_free(2, param_array, line);
	}
	else
		exit_b(line);
}

/**
 * create_child - Creates a child in order to execute another program.
 * @param_array: An array of pointers to strings containing the possible name
 * of a program and its parameters. This array is NULL terminated.
 * @line: The contents of the read line.
 * @count: A counter keeping track of how many commands have been entered
 * into the shell.
 * @av: Name of the program running the shell
 */
void create_child(char **param_array, char *line, int count, char **av)
{
	pid_t id;
	int stts;
	int x;
	int check;
	struct stat buf;
	char *tmp_command;
	char *command;

	id = fork();
	if (id == 0)
	{
		tmp_command = param_array[0];
		command = path_finder(param_array[0]);
		if (command == NULL)
		{
			/*Looking for file in current directory*/
			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				error_printing(av[0], count, tmp_command);
				print_str(": not found", 0);
				single_free(2, line, tmp_command);
				for (x = 1; param_array[x]; x++)
					free(param_array[x]);
				free(param_array);
				exit(100);
			}
			/*file exist in cwd or has full path*/
			command = tmp_command;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0], param_array, environ) == -1)
				exec_error(av[0], count, tmp_command);
		}
	}
	else
		wait(&stts);
}

/**
 * token_interface - Meant to interact with other token functions, and make
 * them more accessible to other parts of the program.
 * @line: A string containing the raw user input.
 * @delim: A constant string containing the desired delimeter to tokenize line.
 * @token_count: A holder for the amount of tokens in a string.
 * Return: Upon success an array of tokens representing the command. Otherwise
 * returns NULL.
 */
char **token_interface(char *line, const char *delim, int token_count)
{
	char **param_array;

	token_count = count_token(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	param_array = tokenize(token_count, line, delim);
	if (param_array == NULL)
	{
		free(line);
		return (NULL);
	}

	return (param_array);
}

/**
 * tokenize - Separates a string into an array of tokens. DON'T FORGET TO FREE
 * on receiving function when using tokenize.
 * @token_count: An integer representing the amount of tokens in the array.
 * @line: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL.
 */
char **tokenize(int token_count, char *line, const char *delim)
{
	int x;
	char **buffer;
	char *tkn;
	char *line_cp;

	line_cp = _strdup(line);
	buffer = malloc(sizeof(char *) * (token_count + 1));
	if (buffer == NULL)
		return (NULL);
	tkn = strtok(line_cp, delim);
	for (x = 0; tkn != NULL; x++)
	{
		buffer[x] = _strdup(tkn);
		tkn = strtok(NULL, delim);
	}
	buffer[x] = NULL;
	free(line_cp);
	return (buffer);
}

/**
 * count_token - Counts tokens in the passed string.
 * @line: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */
int count_token(char *line, const char *delim)
{
	char *str;
	char *tkn;
	int x;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	tkn = strtok(str, delim);
	for (x = 0; tkn != NULL; x++)
		tkn = strtok(NULL, delim);
	free(str);
	return (x);
}
