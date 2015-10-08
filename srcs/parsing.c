/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:30:56 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 14:30:24 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include "get_next_line.h"

#define NO		0
#define START	1
#define END		2

int			ant_number(t_info *info)
{
	char	*line;
	int		ret;

	ret = -1;
	if (get_next_line(0, &line) > 0)
	{
		if (ft_digit(line))
		{
			if (!(info->option & OPT_Q))
				ft_print("%s\n", line);
			ret = ft_atoi(line);
		}
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
			room->ant = 0;
			room->name = ft_strdup(tab[0]);
			room->coord_x = ft_atoi(tab[1]);
			room->coord_y = ft_atoi(tab[2]);
			room->link = NULL;
		}
	}
	ft_freetab(tab);
	return (room);
}

void		verify_comment(t_info *info, int i[3])
{
	i[START] = (!ft_strcmp(info->buffer, "##start")) ? 1 : 0;
	i[END] = (!ft_strcmp(info->buffer, "##end")) ? 1 : 0;
	if ((i[START] || i[END]) && !(info->option & OPT_Q))
		ft_print("%s\n", info->buffer);
}

t_lem		*get_room(t_info *info, int i[3])
{
	t_lem	*room;
	t_lem	*tmp;
	t_lem	*tmp2;

	tmp = NULL;
	while (get_next_line(0, &info->buffer) > 0)
	{
		if (*info->buffer == '#')
		{
			verify_comment(info, i);
			free(info->buffer);
			continue ;
		}
		if (!(tmp2 = treat_room(info->buffer, i[NO]++, i[START], i[END])))
			break ;
		if (!(info->option & OPT_Q))
			ft_print("%s\n", info->buffer);
		room = tmp2;
		room->next = tmp;
		tmp = room;
		ft_bzero(&i[1], sizeof(int) * 2);
		free(info->buffer);
	}
	return (room);
}

t_info		*ft_parse(int option)
{
	t_info	*ret;
	int		info[3];

	if (!(ret = (t_info*)malloc(sizeof(t_info))))
		ft_exit(ret);
	ft_bzero(ret, sizeof(t_info));
	ft_bzero(info, sizeof(int) * 3);
	ret->option = option;
	ret->no_ant = ant_number(ret);
	ret->list = get_room(ret, info);
	get_links(ret->buffer, ret);
	ret->error = 0;
	return (ret);
}
