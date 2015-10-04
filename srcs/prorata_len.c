/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prorata_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/04 18:45:34 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/04 19:56:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

int		get_allpathlen(t_paths *list)
{
	int		total;
	t_paths	*paths;

	total = 0;
	paths = list;
	while (paths)
	{
		paths->len = ft_pathlen(paths->path);
		total += paths->len;
		paths = paths->next;
	}
	return (total);
}

void	set_maxbypath(t_paths *list, int total, int ant)
{
	t_paths	*paths;

	paths = list;
	while (1)
	{
		paths->max = ft_round((float)ant * ((float)paths->len/(float)total));
		ant -= paths->max;
		if (!paths->max || !paths->next)
			break;
		paths = paths->next;
	}
	if (!paths->max)
		paths = paths->prev;
	while (ant < 0)
		paths->max--;
	while (ant > 0)
		list->max++;
}

void	set_prorata_len(t_info *info)
{
	int total;

	total = get_allpathlen(info->paths);
	set_maxbypath(info->paths, total, info->no_ant);
}
