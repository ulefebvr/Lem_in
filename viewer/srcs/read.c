#include "viewer.h"
#include "libft.h"

#include <stdio.h>

int check_line(char *line)
{
	printf("%s [V]\n", line);
	return (1);
}

int read_file(void)
{
	char *buffer;

	while (get_next_line(0, &buffer) && buffer)
	{
		check_line(buffer);
	}
	return (1);
}