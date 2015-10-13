#include "viewer.h"

#include "libft.h"

#include <stdio.h>
int		is_ant(char *line, int lap)
{
	char 	**result;
	int		i;

	i = 0;
	if (line[0] != 'L')
		return (0);
	// Verifier avec un seul deplacement
	if (!(result = ft_strsplit(line, ' ')))
	{
		ft_freetab(result);
		return (0);
	}
	while (result[i])
	{
		if (!lst_add_ant(ft_strsplit(result[i++], '-'), lap))
			return (0);
	}
	return (1);
}

int		check_ant(char *line)
{
	static	int i;
	int		stat;

	if (!line)
	{
		stat = get_next_line(0, &line);
		if (!stat && line == NULL)
			return (-1);
	}
	if (!ft_strlen(line))
		check_ant(NULL);
	if (line[0] != '#' && !is_ant(line, i++))
		return (0);
	return (check_ant(NULL));
}