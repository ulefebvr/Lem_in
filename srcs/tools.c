/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 17:38:06 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/01 13:56:21 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

#include <stdlib.h>

int			ft_tablen(char **tab)
{
	return ((tab && *tab) ? 1 + ft_tablen(++tab) : 0);
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

void		ft_exit(t_info *ret)
{
	t_lem	*list;
	t_lem	*tmp;

	list = NULL;
	if (ret->error)
		write(2, "ERROR\n", 6);
	if (ret != NULL)
	{
		list = ret->list;
		free(ret);
	}
	if (list != NULL)
	{
		while (list)
		{
			tmp = list->next;
			free(list->name);
			free(list);
			list = tmp;
		}
	}
	sleep(5);
	exit(0);
}

int			ft_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str ? 0 : 1);
}