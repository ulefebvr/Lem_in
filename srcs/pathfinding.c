/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 14:18:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/03 17:50:26 by ulefebvr         ###   ########.fr       */
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

t_lem	*get_nextroom(t_info *info, t_lem *room, int start_no)
{
	t_lem	*ret;
	int		i;

	i = 0;
	while (i < 128)
	{
		if (room->link[i] && i != start_no &&
			(!((ret = get_roombyno(info->list, i))->dist) ||
			(ret->dist >	room->link[i] + room->dist)))
			break ;
		else
			ret = NULL;
		i++;
	}
	return (ret);
}


int		find_path(t_info * info, t_lem *room, int start_no)
{
	t_lem	*next;

	while ((next = get_nextroom(info, room, start_no)))
	{
		next->dist = room->dist + room->link[next->no];
		next->path = room;
		if (!next->end)
			find_path(info, next, start_no);
	}
	return(1);
}

int		pathfinder(t_info *info)
{
	t_lem	*start;

	start = get_roomstartend(info->list, 0);
	find_path(info, start, start->no);
	return (1);
}

