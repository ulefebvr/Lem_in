#include "viewer.h"

#include "libft.h"

#include <stdio.h>

char	**is_link(char *line)
{
	char 	**result;

	if (!(result = ft_strsplit(line, '-')) || !(ft_tablen(result) == 2))
	{
		ft_freetab(result);
		return (NULL);
	}
	return ((ft_is_tab_digit(result) ? result : NULL));
}

int		check_link(char *line)
{
	int		stat;

	if (!line)
	{
		stat = get_next_line(0, &line);
		if (!stat && line == NULL)
			return (-1);
	}
	if (!lst_add_link(is_link(line)) && line[0] != '#')
		return (0);
	return (check_link(NULL));
}