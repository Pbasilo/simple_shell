#include "main.h"

/**
 * _strcmp - compares two strings
 * @s: First string
 * @s2: Second string
 * Return: 0 if strings match. -1 Otherwise.
 */
int _strcmp(char *s, char *s2)
{
	int i;

	if (str_len(s) != str_len(s2))
		return (-1);
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != s2[i])
			return (-1);
	}
	return (0);
}

/**
 * _strdup - create a copy of a string
 * @src: Contains the original string
 * Return: Gives back the copy of string
 */
char *_strdup(char *src)
{
	int x;
	int ln;
	char *dest;

	ln = str_len(src);
	dest = malloc(sizeof(char) * (ln + 1));

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}

/**
 * print_str - Prints a string character by character.
 * @str: String to be printed. If the string is NULL it will print (null)
 * @new_line: If integer is 0 a new line will be printed. Otherwise a new line
 * will not be printed.
 */
void print_str(char *str, int new_line)
{
	int x;

	if (str == NULL)
		str = "(null)";
	for (x = 0; str[x] != '\0'; x++)
		write(STDOUT_FILENO, &str[x], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * _write_char - Writes a character to stdout
 * @c: Character that will be written to stdout
 * Return: Upon success how many characters were written.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}
