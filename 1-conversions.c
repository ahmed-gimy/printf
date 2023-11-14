#include "main.h"

/**
 * handle_conv_u - prints an int
 * @conv: va_list
 * @list: va_list
 * Return: int
 */
int handle_conv_u(struct struct_conversion *conv, va_list list)
{
	char *new_all, *new_num;
	int direction, width, len;
	unsigned long int num;

	direction = 1;
	if (conv->starw == 1)
		conv->width = (int)va_arg(list, int);
	if (conv->starp == 1)
		conv->p = (int)va_arg(list, int);
	if (conv->len == 'l')
		num = (unsigned long int)va_arg(list, unsigned long int);
	else if (conv->len == 'h')
		num = (unsigned short int)va_arg(list, unsigned int);
	else
		num = (unsigned int)va_arg(list, unsigned int);
	len = _uintlen(num, 10);
	if (contains(conv->flags, '-'))
		direction = -1;
	if (contains(conv->flags, '.'))
		len++;
	if (contains(conv->flags, '.') && conv->p > len)
		len = conv->p;
	if (!contains(conv->flags, '.') &&
		contains(conv->flags, '0') && conv->width >= len)
		len = conv->width;
	new_num = malloc(sizeof(char) * len);
	if (!new_num)
		exit(1);
	uint_to_str(num, new_num, len, 10, 0);
	width = conv->width > len ? conv->width : len;
	new_all = malloc(sizeof(char) * width);
	if (!new_all)
		free(new_num), exit(1);
	len = assign_width(new_all, new_num, width, len, direction);
	free(new_num);
	free(new_all);
	return (len);
}


/**
 * handle_conv_o - prints an int
 * @conv: va_list
 * @list: va_list
 * Return: int
 */
int handle_conv_o(struct struct_conversion *conv, va_list list)
{
	char *new_all, *new_num;
	int direction, width, len;
	unsigned long int num;

	direction = 1;
	if (conv->starw == 1)
		conv->width = (int)va_arg(list, int);
	if (conv->starp == 1)
		conv->p = (int)va_arg(list, int);
	if (conv->len == 'l')
		num = (unsigned long int)va_arg(list, unsigned long int);
	else if (conv->len == 'h')
		num = (unsigned short int)va_arg(list, unsigned int);
	else
		num = (unsigned int)va_arg(list, unsigned int);
	len = _uintlen(num, 8);
	if (contains(conv->flags, '-'))
		direction = -1;
	if (contains(conv->flags, '#') && num > 0)
		len++;
	if (contains(conv->flags, '.') && conv->p > len)
		len = conv->p;
	if (!contains(conv->flags, '.') && contains(conv->flags, '0')
		&& conv->width >= len)
		len = conv->width;
	new_num = malloc(sizeof(char) * len);
	if (!new_num)
		exit(1);
	uint_to_str(num, new_num, len, 8, 0);
	if (contains(conv->flags, '#') && num > 0)
		new_num[0] = '0';
	width = conv->width > len ? conv->width : len;
	new_all = malloc(sizeof(char) * width);
	if (!new_all)
		free(new_num), exit(1);
	len = assign_width(new_all, new_num, width, len, direction);
	free(new_num);
	free(new_all);
	return (len);
}


/**
 * handle_conv_x - prints an int
 * @conv: va_list
 * @list: va_list
 * Return: int
 */
int handle_conv_x(struct struct_conversion *conv, va_list list)
{
	char *new_all, *new_num;
	int direction, width, len;
	unsigned long int num;

	direction = 1;
	if (conv->starw == 1)
		conv->width = (int)va_arg(list, int);
	if (conv->starp == 1)
		conv->p = (int)va_arg(list, int);
	if (conv->len == 'l')
		num = (unsigned long int)va_arg(list, unsigned long int);
	else if (conv->len == 'h')
		num = (unsigned short int)va_arg(list, unsigned int);
	else
		num = (unsigned int)va_arg(list, unsigned int);
	len = _uintlen(num, 16);
	if (contains(conv->flags, '-'))
		direction = -1;
	if (contains(conv->flags, '.') && conv->p > len)
		len = conv->p;
	if (contains(conv->flags, '#') && num > 0)
		len += 2;
	if (!contains(conv->flags, '.') && contains(conv->flags, '0')
		&& conv->width >= len)
		len = conv->width;
	new_num = malloc(sizeof(char) * len);
	if (!new_num)
		exit(1);
	uint_to_str(num, new_num, len, 16, conv->conv == 'X' ? 1 : 0);
	if (contains(conv->flags, '#') && num > 0)
		new_num[0] = '0', new_num[1] = conv->conv == 'X' ? 'X' : 'x';
	width = conv->width > len ? conv->width : len;
	new_all = malloc(sizeof(char) * width);
	if (!new_all)
		free(new_num), exit(1);
	len = assign_width(new_all, new_num, width, len, direction);
	free(new_num);
	free(new_all);
	return (len);
}

/**
 * handle_conv_S - prints an int
 * @conv: va_list
 * @list: va_list
 * Return: int
 */
int handle_conv_S(__attribute__((unused)) struct struct_conversion *conv,
va_list list)
{
	char nil[] = "(null)";
	char *new, *s;
	int len, i, l;

	s = (char *)va_arg(list, char *);
	if (!s || *s < 0)
		s = nil;
	len = _strlen(s);
	l = len;
	for (i = 0; i < l; i++)
		if ((s[i] > 0 && s[i] < 32) || s[i] >= 127)
			len += 3;
	new = malloc(sizeof(char) * len);
	if (!new)
		exit(1);
	l = 0;
	for (i = 0; i < len; i++)
	{
		if ((s[l] > 0 && s[l] < 32) || s[l] >= 127)
		{
			new[i] = '\\', new[i + 1] = 'x';
			new[i + 2] = (s[l] / 16) >= 10 ? (s[l] / 16 - 10 + 'A') : (s[l] / 16 + '0');
			new[i + 3] = (s[l] % 16) >= 10 ? (s[l] % 16 - 10 + 'A') : (s[l] % 16 + '0');
			i += 3;
			l++;
		}
		else
			new[i] = s[l], l++;
	}
	len = _putstr(new, len);
	free(new);
	return (len);
}


/**
 * handle_conv_p - prints an int
 * @conv: va_list
 * @list: va_list
 * Return: int
 */
int handle_conv_p(struct struct_conversion *conv, va_list list)
{
	char nil[] = "(nil)";
	char *new_all, *new_num;
	int direction, width, len, sign, sp, t;
	unsigned long int num;

	direction = 1, sign = 0, sp = 0, t = 0;
	if (conv->starw == 1)
		conv->width = (int)va_arg(list, int);
	if (conv->starp == 1)
		conv->p = (int)va_arg(list, int);
	num = (unsigned long int)va_arg(list, unsigned long int);
	if (contains(conv->flags, '-'))
		direction = -1;
	len = _uintlen(num, 16) + 2;
	if (contains(conv->flags, '.') && conv->p > len - 2)
		len = conv->p + 2;
	if (contains(conv->flags, '+'))
		len++, sign = 1, t = 1;
	if (!contains(conv->flags, '+') && contains(conv->flags, ' '))
		len++, sp = 1, t = 1;
	new_num = malloc(sizeof(char) * (num ? len : 5));
	if (!new_num)
		exit(1);
	if (num)
	{
		uint_to_str(num, new_num, len, 16, 0);
		new_num[0 + t] = '0', new_num[1 + t] = 'x';
		new_num[0] = (sp == 1 ? ' ' : sign == 1 ? '+' : '0');
	}
	else
		_strcp(new_num, nil), len = 5;
	width = conv->width > len ? conv->width : len;
	new_all = malloc(sizeof(char) * width);
	if (!new_all)
		free(new_num), exit(1);
	len = assign_width(new_all, new_num, width, len, direction);
	free(new_all);
	return (len);
}
