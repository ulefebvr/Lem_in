#include "viewer.h"

#include "libft.h"

#include <stdio.h>
char	**is_link(char *line)
{
	char 	**result;

	if (line[0] == 'L' || !(result = ft_strsplit(line, '-')) || !(ft_tablen(result) == 2))
	{	
		// ft_freetab(result);
		return (NULL);
	}
	return (result);
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
	if (ft_strlen(line) && line[0] != '#' && !lst_add_link(is_link(line)))
		return (check_ant(line));
	return (check_link(NULL));
}