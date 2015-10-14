#include "viewer.h"

#include "libft.h"

int		get_max_longueur(t_ants *ants, int lap)
{
	t_ants	*begin;
	int		max;

	begin = ants;
	max = 0;
	while (ants && ants->lap == lap)
	{
	if (ants->longueur > max)
		max = ants->longueur;
	ants = ants->next;	}	while (ants)
	{
	if (ants->longueur == max && ants->i <= (max / 5))
		return (1);
	ants = ants->prev;
	}
	return (0);
}

int		get_ant_last_step(int ant_num)
{
	t_ants *ants;

	ants = ft_global(NULL)->ants;
	while (ants && ants->next)
		ants = ants->next;
	while (ants)
	{
		if (ants->ant_num == ant_num)
			return (ants->step);
		ants = ants->prev;
	}
	return (get_node_stat("start"));
}

t_map	*get_node_by_num(int num)
{
	t_map *begin;

	begin = ft_global(NULL);
	while (begin->num != num)
		begin = begin->next;
	return (begin);
}

int		get_node_num(char *name)
{
	t_map *map;

	map = ft_global(NULL);
	while (map && ft_strcmp(map->name, name))
		map = map->next;
	return (map->num);
}

int		get_node_stat(char *stat)
{
	t_map *map;

	map = ft_global(NULL);
	while (map && !(!(ft_strcmp(stat, "start")) ? map->start : map->end))
		map = map->next;
	return (map->num);
}
