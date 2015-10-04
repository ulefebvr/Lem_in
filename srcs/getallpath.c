/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getallpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/03 17:31:34 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/04 19:58:14 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdlib.h>

t_path	*translate_path(t_lem *list, t_path *prev)
{
	t_path	*path;

	path = NULL;
	if (list)
	{
		path = (t_path *)malloc(sizeof(t_path));
		path->room = list;
		path->prev = prev;
		path->next = translate_path(list->path, path);
	}
	return (path);
}

t_path	*get_path(t_info *info)
{
	t_path	*path;
	t_lem	*end;
	t_path	*test;

	end = get_roomstartend(info->list, 1);
	path = translate_path(end, NULL);
	return (path);
}

void	remove_path(t_info *info, t_path *path)
{
	t_lem	*list;
	t_path	*tmp;

	list = info->list;
	while (list)
	{
		tmp = path;
		while (tmp)
		{
			if (tmp->room->start || tmp->room->end)
			{
				tmp = tmp->next;
				continue ;
			}
			list->link[tmp->room->no] = 0;
			tmp = tmp->next;
		}
		list->path = NULL;
		list->dist = 0;
		list = list->next;
	}
}

int		verify_path(t_path *list)
{
	int		good;
	t_path	*path;

	good = 0;
	path = list;
	while (path)
	{
		if (path->room->start || path->room->end)
			good++;
		path = path->next;
	}
	return (good == 2);
}

t_paths	*get_allpaths(t_info *info, t_paths *prev)
{
	t_paths *paths;
	t_path	*path;

	paths = NULL;
	pathfinder(info);
	if (verify_path(path = get_path(info)))
	{
		info->no_path += 1;
		paths = (t_paths *)malloc(sizeof(t_paths));
		paths->path = path;
		paths->max = 0;
		paths->len = 0;
		paths->prev = prev;
		remove_path(info, path);
		paths->next = get_allpaths(info, paths);
	}
	else
		free_path(path);
	return (paths);
}
