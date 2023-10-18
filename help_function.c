#include "main.h"
/**
 * str_len - Calculates the lenght of a string.
 * @str: String that needs length to be found.
 * Return: Upon success returns the length of a string. otherwise 0.
 */
int str_len(char *str)
{
	int x;

	if (str == NULL)
		return (0);
	for (x = 0; str[x] != '\0'; x++)
		;
	return (x);
}

/**
 * double_free - Free double pointer variables.
 * @to_be_freed: The address of the elements that need to be freed.
 */
void double_free(char **to_be_freed)
{
	int input;

	for (input = 0; to_be_freed[input] != NULL; input++)
		free(to_be_freed[input]);
	free(to_be_freed);
}

/**
 * single_free - Will free a n amount of pointers to a string.
 * @n: The number of pointers to free.
 */
void single_free(int n, ...)
{
	int x;
	char *str;
	va_list a_list;

	va_start(a_list, n);
	for (x = 0; x < n; x++)
	{
		str = va_arg(a_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}


/**
 * error_printing - Prints a message error when a comand is not found.
 * @count: A counter keeping track of the number of commands run on the shell.
 * @av: The name of the program running the shell.
 * @command: The specific command not being found.
 */
void error_printing(char *av, int count, char *command)
{
	print_str(av, 1);
	print_str(": ", 1);
	print_number(count);
	print_str(": ", 1);
	print_str(command, 1);
}

/**
 * exec_error - Prints exec errors.
 * @av: The name of the program running the shell.
 * @count: Keeps track of how many commands have been entered.
 * @tmp_command: The command that filed.
 */

void exec_error(char *av, int count, char *tmp_command)
{
	error_printing(av, count, tmp_command);
	print_str(": ", 1);
	perror("");
	exit(1);
}
