/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 17:38:06 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/04 19:37:42 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

#include <stdlib.h>

int			ft_tablen(char **tab)
{
	return ((tab && *tab) ? 1 + ft_tablen(++tab) : 0);
}

int			ft_pathlen(t_path *path)
{
	int		i;
	t_path	*begin;

	i = 0;
	begin = path;
	while (++i && (begin = begin->next))
		;
	return (i);
}

int			ft_round(float number)
{
	int		rounder;

	rounder = (int)((number - (int)number) * 10);
	return (rounder >= 5 ? (int)number + 1 : (int)number);
}

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

void		free_list(t_lem *list)
{
	if (list)
	{
		if (list->next)
			free_list(list->next);
		free(list->name);
		free(list);
	}
}

void		ft_exit(t_info *ret)
{
	t_lem	*list;
	t_paths	*paths;

	list = (!ret) ? NULL : ret->list;
	paths = (!ret) ? NULL : ret->paths;
	if (ret->error)
		write(2, "ERROR\n", 6);
	if (ret != NULL)
		free(ret);
	free_list(list);
	free_paths(paths);
	sleep(5);
	exit(0);
}

int			ft_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str ? 0 : 1);
}