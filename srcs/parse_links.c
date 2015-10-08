/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 15:21:16 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 14:21:57 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "get_next_line.h"

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

t_link		*add_link(t_link *links, t_lem *to_add, int dist)
{
	t_link	*new_link;

	if ((new_link = (t_link *)malloc(sizeof(t_link))))
	{
		new_link->room = to_add;
		new_link->dist = dist;
		new_link->next = links;
	}
	return (new_link);
}

int			link_rooms(t_info *info, char *nroom1, char *nroom2)
{
	t_lem	*room1;
	t_lem	*room2;
	int		dist;

	room1 = NULL;
	room2 = NULL;
	if (!(room1 = get_roombyname(info, nroom1)) ||
		!(room2 = get_roombyname(info, nroom2)))
		return (0);
	dist = (info->option & OPT_D) ? distance(room1, room2) : 1;
	room1->link = add_link(room1->link, room2, dist);
	room2->link = add_link(room2->link, room1, dist);
	if (!(info->option & OPT_Q))
		ft_print("%s-%s\n", nroom1, nroom2);
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
		else if (!ft_strlen(line) || *line != '#')
		{
			info->error = 1;
			free(line);
			break ;
		}
		ft_freetab(tab);
		free(line);
		line = NULL;
	}
	return (i);
}
