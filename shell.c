#include "main.h"

/**
 * main - Entry point of the program.
 * @ac: The number of parameters passed to the executable file. In the case
 * this variable will not be used.
 * @av: The name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *lines;
	size_t sze;
	int cmmnd_counter;

	cmmnd_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		cmmnd_counter++;
		lines = NULL;
		sze = 0;
		parse_line(lines, sze, cmmnd_counter, av);

	} while (1);

	return (0);
}
