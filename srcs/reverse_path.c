/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 13:31:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/05 13:42:59 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*reverse_path(t_path *path, int len)
{
	t_path	*ret;
	t_path	*last;
	t_room	*tmp;

	last = path;
	ret = path;
	len = len / 2;
	while (last->next)
		last = last->next;
	while (len--)
	{
		tmp = path->room;
		path->room = last->room;
		last->room = tmp;
	}
}

t_paths	*reverse_all(t_paths *paths)
{
	t_paths	*tmp;

	tmp = paths;
	while (tmp)
	{
		tmp->path = reverse_path(tmp->path, tmp->len);
		tmp = tmp->next;
	}
	return (paths);
}