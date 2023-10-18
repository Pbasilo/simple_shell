#include "main.h"

/**
 * path_finder - Acts as an interface for functions that will be able to
 * find the full path of a program.
 * @command: Represents a command. For example ls, echo, pwd, etc.
 * Return: Upon sucess a string with the full path of the program.
 * for example /bin/ls, /bin/echo, etc. Otherwise returns NULL.
 */
char *path_finder(char *command)
{
	char *str = "PATH";
	char *construct;
	char **path_tokens;
	int index;
	char *dir;

	index = find_path(str);
	path_tokens = tokenize_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	dir = search_directories(path_tokens, command);
	if (dir == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	construct = build_path(dir, command);
	if (construct == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	double_free(path_tokens);

	return (construct);
}
/**
 * find_path - Finds the index of an environmental variable.
 * @str: Environmental variable that needs to be found.
 * Return: Upon success returns the index of the environmental variable.
 * otherwise returns -1.
 */
int find_path(char *str)
{
	int i;
	int ln;
	int j;

	ln = str_len(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < ln; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == ln && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * tokenize_path - Separates a string representing paths as an array
 * of strings contining the path directories.
 * @index: Index of the path in the environment variables.
 * @str: string to separate and tokenize.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL. Note!: Do not forget to free alocated
 * memory on receiving function or when possible.
 */
char **tokenize_path(int index, char *str)
{
	char *env_var;
	int tkn_count;
	const char *delim = ":\n";
	char **path_tokens;
	int ln;

	ln = str_len(str);
	tkn_count = 0;
	/*Moving the pointer ln of str plus = sign*/
	env_var = environ[index] + (ln + 1);
	path_tokens = token_interface(env_var, delim, tkn_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * search_directories - Looks through directories stored in path_tokens for a
 * specific file. aka commmand.
 * @path_tokens: A pointer to an array of strings representing the different
 * paths contained in the PATH environmental varible.
 * @command: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 * Return: Upon success a string with the upper most directory containing
 * the command file. Otherwise returns NULL.
 */
char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cd = getcwd(buf, size);
	if (cd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cd);
			free(cd);
			return (path_tokens[i]);
		}
	}
	chdir(cd);
	free(cd);
	return (NULL);
}

/**
 * build_path - Combines two strings one representing the path directory and
 * one representing the command file.
 * @directory: Represents a directory in the path.
 * @command: Represents a file in a directory of the path.
 * Return: Upon success a string representing the full path of a command.
 * Otherwise NULL.
 */
char *build_path(char *directory, char *command)
{
	int i, j;
	int dir_ln;
	int command_ln;
	int ln;
	char *built;

	if (directory == NULL || command == NULL)
		return (NULL);
	dir_ln = str_len(directory) + 1;
	command_ln = str_len(command) + 1;
	ln = dir_ln + command_ln;

	built = malloc(sizeof(char) * ln);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < ln; i++)
	{
		for (j = 0; directory[j] != '\0'; j++, i++)
			built[i] = directory[j];
		built[i] = '/';
		i++;
		for (j = 0; command[j] != '\0'; j++, i++)
			built[i] = command[j];
	}
	built[--i] = '\0';
	return (built);
}
