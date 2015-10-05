#include "viewer.h"

#include "libft.h"

#include <stdio.h>

static int	*is_comment(char **line, int *comment)
{
	comment[0] = !ft_strcmp(*line, "##start") ? 1 : 0;
	comment[1] = !ft_strcmp(*line, "##end") ? 1 : 0;
	if (comment[0] || comment[1] || *line[0] == '#')
	{
		free(*line);
		get_next_line(0, &(*line));
	}
	return (comment);
}

static int 	get_node(int *comment, char *line)
{
	char **result;

	if (!(result = ft_strsplit(line, ' ')) || !(ft_tablen(result) == 3))
		return (is_link(line) ? check_link(line) : 0);
	return (lst_add(result, comment));
}

static int	check_node()
{
	char	*line;
	int		stat;
	int		comment[2];

	stat = get_next_line(0, &line);
	if (stat < 0 || (line == NULL && !stat))
		return (1);
	stat = get_node(is_comment(&line, comment), line);
	return (stat < 1 ? stat : check_node());
}

int	parse(void)
{
	if (!check_node())
	{
		write(2, "ERROR\n", 6);
		exit(0);
	}
	return (1);
}