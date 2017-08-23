/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <stdio.h>

// prints a string to stdout
static void print(const char *str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		putchar(str[i]);
	}
}

// prints a variable argument list to stdout in the given format
int vprintf(const char *format, va_list args)
{
	size_t i = 0;

	for (; i < strlen(format); i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);
		}
		else
		{
			switch (format[++i])
			{
				case '%':
				{
					putchar('%');
					break;
				}

				case 'c':
				{
					putchar(va_arg(args, char));
					break;
				}

				case 's':
				{
					print(va_arg(args, char*));
					break;
				}

				case 'i':
				case 'd':
				{
					char buf[11] = {0};
					print(itoa(va_arg(args, int), buf, 10));
					break;
				}

				case 'X':
				case 'x':
				{
					char buf[9] = {0};
					print("0x");
					print(itoa(va_arg(args, int), buf, 16));
					break;
				}

				case 'b':
				{
					char buf[33] = {0};
					print("0b");
					print(itoa(va_arg(args, int), buf, 2));
					break;
				}

				case 'o':
				{
					char buf[12] = {0};
					putchar('0');
					print(itoa(va_arg(args, int), buf, 8));
					break;
				}

				default:
				{
					return -1;
					break;
				}
			}
		}
	}

	return i;
}
