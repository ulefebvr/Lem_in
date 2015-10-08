/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 17:38:06 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 14:32:59 by ulefebvr         ###   ########.fr       */
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

t_link		*get_linkbyno(t_link *link, int no)
{
	t_link	*begin;

	begin = link;
	while (begin)
	{
		if (begin->room->no == no)
			break ;
		begin = begin->next;
	}
	return (begin);
}

t_link		*remove_link(t_link *link, int no)
{
	t_link	*begin;
	t_link	*prev;

	begin = link;
	prev = NULL;
	while (begin)
	{
		if (begin->room->no == no && prev)
		{
			prev->next = begin->next;
			free(begin);
			break ;
		}
		if (begin->room->no == no && !prev)
		{
			link = begin->next;
			free(begin);
			break ;
		}
		prev = begin;
		begin = begin->next;
	}
	return (link);
}

int			ft_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str ? 0 : 1);
}
