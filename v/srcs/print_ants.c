/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:01:59 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:02:02 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

#include <unistd.h>

int		is_on_good_way(int node)
{
	t_ants *ants;

	ants = GLOB->ants;
	while (ants)
	{
		if (ants->step == node)
			return (1);
		ants = ants->next;
	}
	return (0);
}

void	calc_ant(t_ants *ants)
{
	t_map *map;
	float x1;
	float x2;
	float y1;
	float y2;

	while (ants)
	{
		map = get_node_by_num(ants->start);
		x1 = (map->x * GLOB->zoom);
		y1 = (map->y * GLOB->zoom);
		map = get_node_by_num(ants->step);
		x2 = (map->x * GLOB->zoom);
		y2 = (map->y * GLOB->zoom);
		if (absi(x2 - x1) >= absi(y2 - y1))
			ants->longueur = absi(x2 - x1);
		else
			ants->longueur = absi(y2 - x1);
		ants->dx = ((x2 - x1) / ants->longueur) * 5;
		ants->dy = ((y2 - y1) / ants->longueur) * 5;
		ants->x = x1 + 0.5;
		ants->y = y1 + 0.5;
		ants->i = 1;
		ants = ants->next;
	}
}

t_ants	*print_ant(t_ants *lista, t_ants *l, int lap)
{
	l = lista;
	sfRenderWindow_drawSprite((sfRenderWindow *)GLOB->window, \
		(sfSprite *)GLOB->background, NULL);
	while (l && l->lap == lap)
	{
		if (l->i <= (l->longueur / 5))
		{
			get_event(GLOB->window);
			GLOB->sprite = (void *)sfSprite_create();
			sfSprite_setTexture((sfSprite *)GLOB->sprite, ((int)l->i % 2) ? \
				(sfTexture *)GLOB->ant1 : (sfTexture *)GLOB->ant2, sfTrue);
			sfSprite_move((sfSprite *)GLOB->sprite, \
				(sfVector2f){l->x - 9, l->y - 11});
			sfRenderWindow_drawSprite((sfRenderWindow *)GLOB->window, \
				(sfSprite *)GLOB->sprite, NULL);
			sfSprite_destroy((sfSprite *)GLOB->sprite);
		}
		l->x += l->dx;
		l->y += l->dy;
		l->i++;
		l = l->next;
	}
	sfRenderWindow_display((sfRenderWindow *)GLOB->window);
	return (usleep(SPEED), lista->i < (lista->longueur / 5) ? lista : l);
}

void	print_them_all(t_ants *list)
{
	int		lap;
	t_ants	*l;
	t_ants	*tmp;

	lap = 0;
	l = NULL;
	calc_ant(list);
	tmp = list;
	while (tmp)
	{
		while ((tmp = print_ant(tmp, l, lap)) && tmp->lap == lap)
			;
		lap++;
	}
}
