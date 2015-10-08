/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 11:10:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 11:13:55 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdlib.h>

void		ft_freetab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void		free_path(t_path *path)
{
	if (path)
	{
		if (path->next)
			free_path(path->next);
		free(path);
	}
}

void		free_paths(t_paths *paths)
{
	if (paths)
	{
		free_path(paths->path);
		if (paths->next)
			free_paths(paths->next);
		free(paths);
	}
}

void		free_links(t_link *link)
{
	if (link)
	{
		if (link->next)
			free_links(link->next);
		free(link);
	}
}

void		free_list(t_lem *list)
{
	if (list)
	{
		if (list->next)
			free_list(list->next);
		free_links(list->link);
		free(list->name);
		free(list);
	}
}
