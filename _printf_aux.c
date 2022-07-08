#include "main.h"
#include <unistd.h>
#include <string.h>

int _putchar(va_list ap, int mode)
{
	char *c = va_arg(ap, char *);

	(void) mode;
	write(1, &c, 1);
	va_end(ap);
	return (1);
}

int singlewrite(char c)
{
	return (write(1, &c, 1));
}

int stringiterator(va_list ap, int mode)
{
	char *s = va_arg(ap, char *);

	(void) mode;
	write(1, s, strlen(s));
	va_end(ap);
	return (strlen(s));
}

int ntostring(va_list ap, int base)
{
	char *buffer;
	int n;
	int i = 0, len, flag;

	n = (va_arg(ap, int));
	buffer = malloc(64);
	flag = ((n < 0) ? 1 : 0);
	n = ((n < 0) ? (n * -1) : n);
	if (n != 0)
	{
		while (n > 0)
		{
			if (base <= 10)
				buffer[i++] = ((n % base) + '0');
			else if (base == 16)
			{
				if ((n % base) >= 10)
					buffer[i++] = ((n % base) + ((base == 32) ? 55 : 87));
				else
					buffer[i++] = ((n % base) + '0');
			}
			n = n / base;
		}
		if (flag && (base == 10))
			buffer[i++] = 45;
		i = ((base == 2) ? i : i - 1);
		for (; i >= 0; i--)
			write(1, &buffer[i], 1);
	} else
	{
		buffer[i] = '0';
		write(1, &buffer[i], 1);
		return (1);
	}
	len = strlen(buffer);
	free(buffer);
	va_end(ap);
	return (len);
}

int ftostring(va_list ap, int precision)
{
	char *buffer;
	double n;
	int i, ppoint, len, mov, apoint;

	n = (va_arg(ap, double));
	mov = 1;
	for (i = 0; i < precision; i++)
		mov = 10 * mov;
	buffer = malloc(64);
	ppoint = (int) n;
	apoint = (int)((n - ppoint) * mov);
	i = 0;
	if (n != 0)
	{
		while (apoint > 0)
		{
			buffer[i++] = ((apoint % 10) + '0');
			apoint = apoint / 10;
		}
		buffer[i++] = 46;
		while ((ppoint > 0) && (i < 63))
		{
			buffer[i++] = ((ppoint % 10) + '0');
			ppoint = ppoint / 10;
		}
		if (n < 1)
			buffer[i++] = '0';
		for (; i >= 0; i--)
			write(1, &buffer[i], 1);
	} else
	{
		buffer[i++] = '0';
		buffer[i++] = '.';
		for (i = 0; i == precision; i++)
			buffer[i++] = '0';
		write(1, buffer, (strlen(buffer)));
		return (1);
	}
	len = strlen(buffer);
	free(buffer);
	va_end(ap);
	return (len);
}