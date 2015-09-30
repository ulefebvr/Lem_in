/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:30:56 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 17:59:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "get_next_line.h"

#include <stdio.h> //printf

int			ant_number(void)
{
	char	*line;
	int		ret;

	ret = -1;
	if (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
			ret = ant_number();
		else if (ft_digit(line))
			ret = ft_atoi(line);
		free(line);
	}
	return (ret);
}

t_lem		*treat_room(char *line, int number)
{
	t_lem	*room;
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (!tab || ft_tablen(tab) != 3 ||
		!ft_digit(tab[1]) || !ft_digit(tab[2]))
		room = NULL;
	else
	{
		if ((room = (t_lem *)malloc(sizeof(t_lem))))
		{
			room->no = number;
			room->name = ft_strdup(tab[0]);
			room->coord_x = ft_atoi(tab[1]);
			room->coord_y = ft_atoi(tab[2]);
		}
		else
			room = NULL;
	}
	ft_freetab(tab);
	return (room);
}

t_lem		*get_room(int number, int ant_n, int start, int end)
{
	char	*line;
	t_lem	*begin;

	line = NULL;
	if (get_next_line(0, &line) <= 0)
		return (NULL);
	if (*line == '#')
	{
		if (!ft_strcmp(line, "##start"))
			start = 1;
		if (!ft_strcmp(line, "##end"))
			end = 1;
		free(line);
		get_room(number, 0, start, end);
	}
	if (!(begin = treat_room(line, number)))
		return (NULL);
	begin->ant = ant_n;
	begin->start = start;
	begin->end = end;
	begin->next = get_room(++number, 0, 0, 0);
	free(line);
	return (begin);
}

t_info		*ft_parse(void)
{
	t_info	*ret;

	if (!(ret = (t_info*)malloc(sizeof(t_info))) ||
		(ret->no_ant = ant_number()) == -1 ||
		!(ret->list = get_room(0, ret->no_ant, 0, 0)))
		ft_exit(ret);
	return (ret);
}

int			main(void)
{
	t_info	*info;

	info = ft_parse();
	printf("%d\n", info->no_ant);
	free(info);
	return(1);
}
