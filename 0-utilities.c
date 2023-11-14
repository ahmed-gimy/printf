#include "main.h"
/**
 * contains - print strings
 * @s: - char to sperate ints
 * @c: - char to sperate ints
 * Return: int
 */
int contains(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return (1);
	return (0);
}

/**
 * _putstr - print strings
 * @s: - char to sperate ints
 * @n: - char to sperate ints
 * Return: int
 */
int _putstr(char *s, unsigned int n)
{
	return (write(1, s, n));
}

/**
 * _strlen - print strings
 * @s: - char to sperate ints
 * Return: int
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0';)
		i++;
	return (i);
}

/**
 * _strcp - print strings
 * @to: - char to sperate ints
 * @from: - char to sperate ints
 */
void _strcp(char *to, char *from)
{
	int i;

	for (i = 0; from[i] != '\0'; i++)
		to[i] = from[i];
}
