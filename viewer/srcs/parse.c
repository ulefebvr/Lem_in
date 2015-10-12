#include "viewer.h"

#include "libft.h"

static char	*begin_parse(void)
{
	char *line;
	char **result;
	
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		result = ft_strsplit(line, ' ');
		if (line[0] == '#' || (ft_strchr(line, ' ') && ft_tablen(result) == 3))
			return (line);
	}
	return (NULL);
}

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

	if (!ft_strlen(line))
	{
		free(line);
		return (1);
	}
	if (!(result = ft_strsplit(line, ' ')) || (ft_tablen(result) != 3))
	{
		if (result)	
			ft_freetab(result);
		return (is_link(line) ? check_link(line) : 0);
	}
	free(line);
	return (lst_add(result, comment));
}

static int	check_node(char *line)
{
	int		stat;
	int		comment[2];

	if (!line)
	{
		stat = get_next_line(0, &line);
		if (stat < 0 || (line == NULL && !stat))
			return (0);
	}
	stat = get_node(is_comment(&line, comment), line);
	return (stat < 1 ? stat : check_node(NULL));
}

int	parse(void)
{
	if (!check_node(begin_parse()))
	{
		write(2, "ERROR\n", 6);
		exit(0);
	}
	return (1);
}