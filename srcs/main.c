/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 10:17:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/04 21:12:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"
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
 	t_paths	*paths;
 	t_path	*path;
	int		i;
 
 	info = ft_parse();
 	// printf("%d\n", info->no_ant);

 	// list = info->list;
 	// while (list)
 	// {
		// i = 0;
 	// 	printf("{no:%d, name:%s, ant:%d, start/end: %d/%d, coord: %d,%d\n", 
 	// 		list->no, list->name, list->ant, list->start, list->end,
 	// 		list->coord_x, list->coord_y);
		// while (i < 10)
		// 	printf("%d ", list->link[i++]);
		// printf("\n");
 	// 	list = list->next;
 	// }
 	// printf("main done\n");
 	// pathfinder(info);
 	// list = get_endroom(info->list);
 	// while (list)
 	// {
 	// 	sleep(5);
 	// 	printf("%s\n", list->name);
 	// 	list = list->path;
 	// }

	info->no_path = 0;
 	info->paths = get_allpaths(info, NULL);
 	// sendtopath(info);
 	set_prorata_len(info);
 	paths = info->paths;
 	printf("how much path available === %d\n", info->no_path);
 	while (paths)
 	{
 		printf("path len : %d\n", paths->len);
 		printf("max to pass %d\n", paths->max);
 		path = paths->path;
 		while (path)
 		{
	 		printf("%s\n", path->room->name);
	 		path = path->next;
	 	}
	 	printf("===============\n");
	 	paths = paths->next;
 	}
 	printf("\n\n\n");
 	sendtopath(info);
 	ft_exit(info);
 
 
 	// int i = 0;
 	// char *line;
 	// line = NULL;
 	// while ((i = get_next_line(0, &line)))
 	// {
 	// 	printf("%d : %s\n", i, line);
 	// 	free(line);
 	// 	line = NULL;
 	// }
 	// sleep(5);
 	// return(1);
 }