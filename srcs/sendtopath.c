/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtopath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/03 17:31:34 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/03 17:50:02 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdlib.h>

t_path	*translate_path(t_lem *list)
{
	t_path	*path;

	path = NULL;
	if (list)
	{
		path = (t_path *)malloc(sizeof(t_path));
		path->room = list;
		path->next = translate_path(list->path);
	}
	return (path);
}

t_path	*get_path(t_info *info)
{
	t_path	*path;
	t_lem	*end;

	end = get_roomstartend(info->list, 1);
	path = translate_path(end);
	return (path);
}