/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:30:56 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/01 15:33:56 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "get_next_line.h"

#define NO		0
#define START	1
#define END		2
#define ANT		3

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

t_lem		*treat_room(char *line, int number, int start, int end)
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
			ft_bzero(room, sizeof(t_lem));
			room->no = number;
			room->start = start;
			room->end = end;
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

t_lem		*get_room(t_info *info, int inf[4])
{
	t_lem	*begin;
	char	*line;

	line = NULL;
	if (get_next_line(0, &line) <= 0)
		return (NULL);
	if (*line == '#')
	{
		inf[START] = (!ft_strcmp(line, "##start")) ? 1 : 0;
		inf[END] = (!ft_strcmp(line, "##end")) ? 1 : 0;
		free(line);
		return(get_room(info, inf));
	}
	if (!(begin = treat_room(line, inf[NO], inf[START], inf[END])))
	{
		info->buffer = line;
		return (NULL);
	}
	begin->ant = (inf[START]) ? inf[ANT] : 0;
	inf[NO]++;
	ft_bzero(&inf[1], sizeof(int) * 2);
	begin->next = get_room(info, inf);
	return (free(line), begin);
}

t_info		*ft_parse(void)
{
	t_info	*ret;
	int		info[4];

	if (!(ret = (t_info*)malloc(sizeof(t_info))))
		ft_exit(ret);
	ft_bzero(ret, sizeof(t_info));
	ft_bzero(info, sizeof(int) * 4);
	if ((info[ANT] = ant_number()) == -1 ||
		!(ret->list = get_room(ret, info)) ||
		get_links(ret->buffer, ret) == -1)
	{
		ret->error = 1;
		ft_exit(ret);
	}
	ret->no_ant = info[ANT];
	return (ret);
}
