/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 14:18:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 10:41:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdlib.h>

t_lem	*get_roomstartend(t_lem *list, int end)
{
	t_lem	*begin;

	begin = list;
	while (begin)
	{
		if (end ? begin->end : begin->start)
			break ;
		begin = begin->next;
	}
	return (begin);
}

t_lem	*get_roombyno(t_lem *list, int no)
{
	t_lem *begin;

	begin = list;
	while (begin)
	{
		if (begin->no == no)
			break ;
		begin = begin->next;
	}
	return (begin);
}

t_lem	*get_nextroom(t_lem *room)
{
	t_lem	*ret;
	t_link	*link;
	int		i;

	i = 0;
	link = room->link;
	while (link)
	{
		if (!link->room->start && (!((ret = link->room)->dist) ||
			(link->room->dist > link->dist + room->dist)))
			break ;
		link = link->next;
	}
	if (!link)
		ret = NULL;
	return (ret);
}

int		find_path(t_info *info, t_lem *room, int start_no)
{
	t_lem	*next;

	while ((next = get_nextroom(room)))
	{
		next->dist = room->dist + get_linkbyno(room->link, next->no)->dist;
		next->path = room;
		if (!next->end)
			find_path(info, next, start_no);
	}
	return (1);
}

int		pathfinder(t_info *info)
{
	t_lem	*start;

	start = get_roomstartend(info->list, 0);
	find_path(info, start, start->no);
	return (1);
}
