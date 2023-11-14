#include "main.h"

/**
 * assign_width - print strings
 * @new: - char to sperate ints
 * @s: - char to sperate ints
 * @total_width: - char to sperate ints
 * @width: - char to sperate ints
 * @direction: - char to sperate ints
 * Return: int
 */
int assign_width(char *new, char *s, int total_width, int width, int direction)
{
	if (direction > 0)
		return (assign_width_pos(new, s, total_width, width));
	else
		return (assign_width_neg(new, s, total_width, width));
}

/**
 * assign_width_pos - print strings
 * @new: - char to sperate ints
 * @s: - char to sperate ints
 * @total_width: - char to sperate ints
 * @width: - char to sperate ints
 * Return: int
 */
int assign_width_pos(char *new, char *s, int total_width, int width)
	{
	int i;

	for (i = total_width - 1; i >= 0; i--)
	{
		if (width > 0)
		{
			new[i] = s[width - 1];
			width--;
		}
		else
		new[i] = ' ';
	}
	return (_putstr(new, total_width));
}

/**
 * assign_width_neg - print strings
 * @new: - char to sperate ints
 * @s: - char to sperate ints
 * @total_width: - char to sperate ints
 * @width: - char to sperate ints
 * Return: int
 */
int assign_width_neg(char *new, char *s, int total_width, int width)
{
	int i;

	for (i = 0; i < total_width; i++)
	{
		if (width > i)
			new[i] = s[i];
		else
			new[i] = ' ';
	}
	return (_putstr(new, total_width));
}
