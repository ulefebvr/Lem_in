/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtopath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/04 19:55:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/05 16:07:57 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

int		move_path(t_path *path)
{
	int		move;

	move = 0;
	if (path)
	{
		move += move_path(path->next);
		if (path->next && !path->room->start && path->room->ant)
		{
			ft_print("L%d-%s ", path->room->ant, path->next->room->name);
			path->next->room->ant = path->room->ant;
			path->room->ant = 0;
			move++;
		}
	}
	return (move);
}

int		first_move(t_info *info, t_paths *paths, int ant)
{
	ft_print("L%d-%s ", ant - info->no_ant + 1, paths->path->next->room->name);
	paths->path->next->room->ant = ant - info->no_ant + 1;
	info->no_ant--;
	paths->max--;
	return (1);
}

int		move_ant(t_info *info, int total_ant)
{
	t_paths		*paths;
	int			move;

	move = 0;
	paths = info->paths;
	while (paths)
	{
		move += move_path(paths->path);
		if (paths->max)
			move += first_move(info, paths, total_ant);
		paths = paths->next;
	}
	return (move);
}

void	sendtopath(t_info *info)
{
	int		total_ant;

	total_ant = info->no_ant;
	while (move_ant(info, total_ant))
		ft_print("\n");
}