/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:00:56 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:00:57 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

#include <stdlib.h>

void	ft_free_ants(t_ants *ants)
{
	t_ants *save;

	while (ants)
	{
		save = ants;
		ants = ants->next;
		free(save);
	}
}

void	ft_free_links(t_links *links)
{
	t_links *save;

	while (links)
	{
		save = links;
		links = links->next;
		free(save);
	}
}

void	ft_free_struct(t_map *map, sfRenderWindow *window)
{
	t_map *save;

	sfCircleShape_destroy(ft_global(NULL)->circle);
	sfRenderWindow_destroy(window);
	while (map)
	{
		save = map;
		map = map->next;
		ft_free_ants(save->ants);
		ft_free_links(save->links);
		free(save);
	}
}
