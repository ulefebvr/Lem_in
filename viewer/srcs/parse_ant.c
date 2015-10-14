#include "viewer.h"

#include "libft.h"

int		is_ant(char *line, int lap)
{
	char 	**result;
	int		i;

	i = 0;
	if (line[0] != 'L')
		return (0);
	// Verifier avec un seul deplacement
	if (!(result = ft_strsplit(line, ' ')))
		return (ft_freetab(result), 0);
	while (result[i])
	{
		if (!lst_add_ant(ft_strsplit(result[i++], '-'), lap))
			return (ft_freetab(result), 0);
	}
	ft_freetab(result);
	free(line);
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
			return (free(line), -1);
	}
	if (!ft_strlen(line))
	{
		free(line);
		check_ant(NULL);
	}
	if (line[0] != '#' && !is_ant(line, i++))
		return (free(line), 0);
	return (check_ant(NULL));
}