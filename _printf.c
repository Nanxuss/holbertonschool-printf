#include "main.h"
#include <unistd.h>
#include <stddef.h>

/**
 * singlewrite - write a single character
 * @c: character to write
 *
 * Return: 1
 */

int singlewrite(char c)
{
	return (write(1, &c, 1));
}

/**
 * _printf - print string to stdout using variable arguments
 * @format: template string to print
 *
 * Return: string length
 */

int _printf(const char *format, ...)
{
	int i = 0, j = 0;
	ftype func_data;
	va_list ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
		while ((format[i] != '\0') && (format != NULL))
		{
			if ((format[i] == 37) && (format[i + 1] != 37) && (format[i + 1] != '\0'))
			{
				func_data = func_finder(format[i + 1]);
				if (func_data.op != NULL)
				{
					j += (*(func_data.op))(ap, func_data.mode);
					i += 2;
				} else
				{
					j += singlewrite(format[i++]);
					j += singlewrite(format[i++]);
				}
			}
			else if ((format[i] == '%') && (format[i + 1] == '\0'))
			{
				if (i == 0)
					return (-1);
				continue;
			}
			else if ((format[i] == '%') && (format[i + 1] == '%'))
			{
				j += singlewrite(format[i++]);
				i++;
			} else
				j += singlewrite(format[i++]);
		}
	va_end(ap);
	return (j);
}
