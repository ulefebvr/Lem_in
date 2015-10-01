/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 15:21:16 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/01 15:22:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

t_lem		*get_roombyname(t_info *info, char *name)
{
	t_lem	*begin;

	begin = info->list;
	while (begin)
	{
		if (!ft_strcmp(name, begin->name))
			break ;
		begin = begin->next;
	}
	return (begin);
}

int			link_rooms(t_info *info, char *nroom1, char *nroom2)
{
	t_lem	*room1;
	t_lem	*room2;

	if (!(room1 = get_roombyname(info, nroom1))||
		!(room2 = get_roombyname(info, nroom2)))
		ft_exit(info);
	room1->link[room2->no] = 1;
	room2->link[room1->no] = 1;
	return (1);
}

int			get_links(char *line, t_info *info)
{
	char	**tab;
	int		i;

	while (1)
	{
		if (!line && (i = get_next_line(0, &line)) <= 0)
			break ;
		if ((ft_tablen(tab = ft_strsplit(line, '-'))) == 2)
			link_rooms(info, tab[0], tab[1]);
		ft_freetab(tab);
		free(line);
		line = NULL;
	}
	return (i);
}