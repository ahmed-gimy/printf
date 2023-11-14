#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

struct struct_conversion
{
	char conv;
	char len;
	char *flags;
	int p;
	int width;
	int starp;
	int starw;
};

typedef int (*conv_actions)(struct struct_conversion *, va_list);

int _printf(const char *format, ...);
void define_consts(conv_actions *conversions);
void init_conv(struct struct_conversion *conv, char *conv_flag);
void valid_exp(char *s, struct struct_conversion *conv);
int to_int(char **s);

int _putstr(char *s, unsigned int n);
int contains(char *s, char c);
int _strlen(char *s);
void _strcp(char *to, char *from);

int assign_width(char *new, char *s, int total_width, int width, int direction);
int assign_width_pos(char *new, char *s, int total_width, int width);
int assign_width_neg(char *new, char *s, int total_width, int width);

void int_to_str(long int num, char *new_num, int len, int sign);
void uint_to_str(unsigned long int num, char *new_num, int len, unsigned int base, int uppercase);
int _intlen(long int num, int base);
int _uintlen(unsigned long int num, unsigned int base);

int handle_conv_c(struct struct_conversion *conv, va_list list);
int handle_conv_s(struct struct_conversion *conv, va_list list);
int handle_conv_percent(struct struct_conversion *conv, va_list list);
int handle_conv_i(struct struct_conversion *conv, va_list list);
int handle_conv_b(struct struct_conversion *conv, va_list list);

int handle_conv_u(struct struct_conversion *conv, va_list list);
int handle_conv_o(struct struct_conversion *conv, va_list list);
int handle_conv_x(struct struct_conversion *conv, va_list list);
int handle_conv_S(struct struct_conversion *conv, va_list list);
int handle_conv_p(struct struct_conversion *conv, va_list list);

int handle_conv_r(struct struct_conversion *conv, va_list list);
int handle_conv_R(struct struct_conversion *conv, va_list list);

#endif
