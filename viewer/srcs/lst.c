#include "viewer.h"

#include "libft.h"
#include <stdlib.h>

#include "stdio.h"

static int	get_node_num(char *name)
{
	t_map *map;

	map = ft_global(NULL);
	while (map && ft_strcmp(map->name, name))
		map = map->next;
	return (map->num);
}

int	lst_add_link(char **link)
{
	t_links	*new;
	t_links	*begin;
	t_map	*map;

	if (link[0][0] == '#')
		return (0);
	map = ft_global(NULL);
	new = (t_links *)malloc(sizeof(t_links));
	new->node = get_node_num(link[1]) ? get_node_num(link[1]) : 0;
	new->next = NULL;
	while (map && ft_strcmp(map->name, link[0]))
		map = map->next;
	begin = map->links;
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
	else
		map->links = new;
	return (1);
}

int	lst_add(char **info, int *comment)
{
	t_map *new;
	t_map *begin;
	
	begin = ft_global(NULL);
	new = (t_map *)malloc(sizeof(t_map));
	new->start = comment[0];
	new->end = comment[1];
	new->name = ft_strdup(info[0]);
	new->x = ft_atoi(info[1]);
	new->y = ft_atoi(info[2]);
	new->links = NULL;
	new->next = NULL;
	ft_freetab(info);
	if (!begin)
		ft_global(new);
	else
	{
		while(begin->next)
			begin = begin->next;
		new->num = begin->num + 1;
		begin->next = new;
	}
	return (1);
}