#include "main.h"

/**
 * print_number - Prints an unsigned number
 * @x: unsigned integer to be printed
 * Return: The amount of numbers printed
 */
int print_number(int x)
{
	int div;
	int ln;
	unsigned int num;

	div = 1;
	ln = 0;

	num = x;

	for (; num / div > 9; )
		div *= 10;

	for (; div != 0; )
	{
		ln += _write_char('0' + num / div);
		num %= div;
		div /= 10;
	}

	return (ln);
}
