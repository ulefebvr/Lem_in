/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:01:19 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:01:19 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

#include "libft.h"
#include <stdlib.h>

int	lst_add_ant(char **ants, int lap)
{
	t_ants *new;
	t_ants *begin;

	if (!ft_tablen(ants))
		return (0);
	begin = ft_global(NULL)->ants;
	new = (t_ants *)malloc(sizeof(t_ants));
	new->ant_num = ft_atoi(&ants[0][1]);
	new->start = get_ant_last_step(new->ant_num);
	new->step = get_node_num(ants[1]);
	new->lap = lap;
	new->next = NULL;
	new->prev = NULL;
	if (!begin)
		ft_global(NULL)->ants = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		new->prev = begin;
		begin->next = new;
	}
	ft_freetab(ants);
	return (1);
}

int	lst_add_link(char **link)
{
	t_links	*new;
	t_links	*begin;
	t_map	*map;

	if (!link)
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
	ft_freetab(link);
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
	new->x = ft_atoi(info[1]) + 1;
	new->y = ft_atoi(info[2]) + 1;
	new->links = NULL;
	new->ants = NULL;
	new->next = NULL;
	ft_freetab(info);
	if (!begin)
		ft_global(new);
	else
	{
		while (begin->next)
			begin = begin->next;
		new->num = begin->num + 1;
		begin->next = new;
	}
	return (1);
}
