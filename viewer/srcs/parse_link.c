#include "viewer.h"

#include "libft.h"

char	**is_link(char *line)
{
	char 	**result;

	result = NULL;
	if (line[0] == 'L' || !(result = ft_strsplit(line, '-')) || !(ft_tablen(result) == 2))
	{	
		ft_freetab(result);
		return (NULL);
	}
	return (result);
}

int		check_link(char *line)
{
	int		stat;
	static int i;

	if (!line)
	{
		stat = get_next_line(0, &line);
		if (stat < 0 || (line == NULL && !stat))
		{
			free(line);
			return (-1);
		}
	}
	if (ft_strlen(line) && line[0] != '#' && !lst_add_link(is_link(line)))
		return (i ? check_ant(line) : 0);
	free(line);
	return (i++, check_link(NULL));
}