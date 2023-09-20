#include "my_shell.h"

/**
 * long_to_string - Converts a number to a string.
 * @number: The number to be converted to a string.
 * @string: The buffer to save the number as a string.
 * @base: The base to convert the number.
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, isNegative = 0;
	long quotient = number;
	char letters[] = "0123456789abcdef";

	if (quotient == 0)
		string[index++] = '0';

	if (string[0] == '-')
		isNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[index++] = letters[-(quotient % base)];
		else
			string[index++] = letters[quotient % base];
		quotient /= base;
	}

	if (isNegative)
		string[index++] = '-';

	string[index] = '\0';
	custom_str_reverse(string);
}

/**
 * atoi_custom - Convert a string to an integer.
 * @s: Pointer to the source string.
 *
 * Return: Integer value of the string or 0.
 */
int atoi_custom(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while (*s)
	{
		if (*s == '-')
			sign = -sign;
		else if (*s >= '0' && *s <= '9')
			number = number * 10 + (*s - '0');
		else if (number > 0)
			break;
		s++;
	}

	return (sign * number);
}

/**
 * count_characters - Count the occurrences of a character in a  * string.
 * @string: Pointer to the source string.
 * @character: String containing characters to count.
 *
 * Return: The count of occurrences of the character in the string.
 */
int count_characters(char *string, char *character)
{
	int count = 0;

	while (*string)
	{
	if (*string == character[0])
		count++;
	string++;
	}

	return (count);
}

