/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 10:17:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/05 19:58:35 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

t_lem	*get_endroom(t_lem *list)
{
	t_lem	*begin;

	begin = list;
	while (begin)
	{
		if (begin->end)
			break ;
		begin = begin->next;
	}
	return (begin);
}

 int			main(void)
 {
	t_info	*info;

	info = ft_parse();
	info->no_path = 0;

	// t_lem *begin = info->list;
	// t_link	*link;
	// while (begin)
	// {
	// 	ft_print("%s %d\n", begin->name, begin->no);
	// 	link = begin->link;
	// 	while (link)
	// 	{
	// 		ft_print("linked to room no %d named %s", link->room->no, link->room->name);
	// 		link = link->next;
	// 	}
	// 	begin = begin->next;
	// }
	// ft_print("done\n");

	info->paths = get_allpaths(info, NULL);
	set_prorata_len(info);
	// info->paths = reverse_all(info->paths);
	sendtopath(info);
	ft_exit(info);
 }