#include "main.h"

/**
 * _printf - print strings
 * @format: - char to sperate ints
 * Return: int
 */
int _printf(const char *format, ...)
{
	int i, sum;
	conv_actions conversions['z' - '%'], func;
	char conv_flag[5], *s;
	struct struct_conversion conv;
	va_list list;

	if (!format)
		return (-1);
	sum = 0;
	s = (char *)format;
	define_consts(conversions);
	va_start(list, format);
	for (i = 0; s[i] != '\0'; i++)
	{
		init_conv(&conv, conv_flag);
		if (s[i] == '%')
		{
			valid_exp(s + i + 1, &conv);
			if (conv.conv != '\0')
			{
				if (conv.conv - '%' >= 0 && conv.conv - '%' < 'z' - '%' && conversions[conv.conv - '%'])
				{
					sum += _putstr(s, i), i++;
					while (s[i] != conv.conv)
						i++;
					s += i + 1;
					i = -1;
					func = conversions[conv.conv - '%'];
					sum += func(&conv, list);
				}
			}
			else
			{
				_putstr(s, i);
				return (-1);
			}
		}
	}
	sum = sum + _putstr(s, i);
	va_end(list);
	return (sum);
}

/**
 * define_consts - print strings
 * @conversions: - char to sperate ints
 */
void define_consts(conv_actions *conversions)
{
	int i;

	for (i = 0; i < 'z' - '%'; i++)
		conversions[i] = NULL;

	conversions['c' - '%'] = handle_conv_c;
	conversions['s' - '%'] = handle_conv_s;
	conversions['%' - '%'] = handle_conv_percent;
	conversions['i' - '%'] = handle_conv_i;
	conversions['d' - '%'] = handle_conv_i;
	conversions['b' - '%'] = handle_conv_b;
	conversions['u' - '%'] = handle_conv_u;
	conversions['o' - '%'] = handle_conv_o;
	conversions['x' - '%'] = handle_conv_x;
	conversions['X' - '%'] = handle_conv_x;
	conversions['S' - '%'] = handle_conv_S;
	conversions['p' - '%'] = handle_conv_p;
	conversions['r' - '%'] = handle_conv_r;
	conversions['R' - '%'] = handle_conv_R;
}

/**
 * valid_exp - print strings
 * @s: - char to sperate ints
 * @conv: - char to sperate ints
 */
void valid_exp(char *s, struct struct_conversion *conv)
{
	char conv_flags[6] = "\0\0\0\0\0\0", *local_s;
	char flags[] = "+ 0-.#";
	int i, flag_i, p, num;

	local_s = s;
	flag_i = 0, p = 0;
	for (i = 0; local_s[i] != '\0'; i++)
	{
		if (contains(flags, local_s[i]) == 1 && p == 0 && (conv->width == 0 || local_s[i] == '.'))
		{
			if (conv->starp == 1 || (conv->starw == 1 && local_s[i] != '.'))
			{
				conv->conv = local_s[i];
				return;
			}
			if (local_s[i] == '.')
				p++;
			if (contains(conv_flags, local_s[i]) == 0)
			{
			conv_flags[flag_i] = local_s[i];
			flag_i++;
			}
		}
		else if (((local_s[i - 1] == '.' && p == 1 && conv->starp == 0) || (p == 0 && conv->width == 0 &&  conv->starw == 0)) && local_s[i] == '*')
		{
			if (local_s[i - 1] == '.' && p == 1 && conv->starp == 0)
				conv->starp = 1;
			else if (p == 0 && conv->width == 0 &&  conv->starw == 0)
				conv->starw = 1;
		}
		else if (local_s[i] >= '0' && local_s[i] <= '9' &&
			((conv->width == 0 && p == 0 && conv->starw == 0) ||
			(conv->p == 0 && p == 1 && conv->starp == 0)))
		{
			local_s += i;
			i = -1;
			num = to_int(&local_s);
			if (conv->width == 0 && p == 0)
				conv->width = num;
			else
				conv->p = num;
		}
		else if (local_s[i] == 'l' || local_s[i] == 'h')
		{
			conv->len = local_s[i];
			conv->conv = local_s[i + 1];
			_strcp(conv->flags, conv_flags);
			return;
		}
		else
		{
			conv->conv = local_s[i];
			_strcp(conv->flags, conv_flags);
			return;
		}
	}
}

/**
 * init_conv - print strings
 * @conv: - char to sperate ints
 * @conv_flag: - char to sperate ints
 */
void init_conv(struct struct_conversion *conv, char *conv_flag)
{
	int i;
	for (i = 0; i < 5; i++)
		conv_flag[i] = '\0';
	conv->len = '\0';
	conv->conv = '\0';
	conv->flags = conv_flag;
	conv->p = 0;
	conv->width = 0;
	conv->starp = 0;
	conv->starw = 0;
}

/**
 * to_int - print strings
 * @s: - char** to sperate ints
 * Return: int
 */
int to_int(char **s)
{
	int i, val;

	val = 0;
	for (i = 0; (*s)[i] >= '0' && (*s)[i] <= '9'; i++)
	{
		val *= 10;
		val += (*s)[i] - '0';
	}
	*s += i;
	return (val);
}
