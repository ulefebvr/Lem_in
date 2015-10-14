/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:01:54 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:01:54 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

#include "SFML/Audio.h"
#include "SFML/Config.h"
#include "SFML/Network.h"
#include "SFML/OpenGL.h"
#include "SFML/System.h"
#include "SFML/Window.h"
#include "libft.h"

void	ft_update_texture(sfRenderTexture *texture, sfRenderWindow *window)
{
	sfSprite		*sprite;
	const sfTexture	*f_texture;

	sprite = sfSprite_create();
	sfRenderTexture_display(texture);
	f_texture = sfRenderTexture_getTexture(texture);
	sfSprite_setTexture(sprite, f_texture, sfTrue);
	GLOB->background = sprite;
	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfRenderWindow_display(window);
	GLOB->window = (void *)window;
	GLOB->sprite = (void *)sprite;
	GLOB->f_texture = (void *)f_texture;
}

void	draw_node(sfRenderTexture *texture, t_map *map)
{
	sfCircleShape *circle;

	circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, GLOB->node_size);
	GLOB->circle = (void *)circle;
	while (map)
	{
		sfCircleShape_setPosition(circle, (sfVector2f){((map->x) * GLOB->zoom) \
			- GLOB->node_size, ((map->y) * GLOB->zoom) - GLOB->node_size});
		if (map->start)
			sfCircleShape_setFillColor(circle, MYGREEN);
		else if (map->end)
			sfCircleShape_setFillColor(circle, MYBLUE);
		else
			sfCircleShape_setFillColor(circle, MYGREY);
		if (is_on_good_way(map->num))
		{
			sfCircleShape_setOutlineThickness(circle, 2.5);
			sfCircleShape_setOutlineColor(circle, MYBLUE);
		}
		sfRenderTexture_drawCircleShape(texture, circle, NULL);
		map = map->next;
	}
}

void	draw_background(sfRenderTexture **texture, sfRenderWindow *window)
{
	t_links	*save;
	t_map	*map;

	map = GLOB;
	sfRenderWindow_clear(window, MYBROWN);
	sfRenderTexture_clear(*texture, MYBROWN);
	while (map)
	{
		if (map->links)
			save = map->links;
		while (save)
		{
			draw_line(map->num, save->node, *texture);
			save = save->next;
		}
		map = map->next;
	}
	draw_node(*texture, GLOB);
}

int		ft_get_window(void)
{
	sfRenderTexture	*texture;
	sfRenderWindow	*window;

	texture = sfRenderTexture_create(WIDTH, HEIGHT, 64);
	window = (sfRenderWindow *)GLOB->window;
	GLOB->zoom = GLOB->zoom ? GLOB->zoom : ZOOM;
	GLOB->node_size = GLOB->zoom / 3 ? GLOB->zoom / 3 : 1;
	if (!(sfRenderWindow *)GLOB->window)
		return (0);
	draw_background(&texture, window);
	ft_update_texture(texture, window);
	return (1);
}

int		print_all(void)
{
	sfRenderWindow	*window;

	window = NULL;
	GLOB->zoom = 0;
	GLOB->window = (void *)sfRenderWindow_create((sfVideoMode){WIDTH, \
		HEIGHT, 64}, "SFML window", sfResize | sfClose, NULL);
	ft_get_window();
	ft_set_perso();
	window = GLOB->window;
	while (sfRenderWindow_isOpen(window))
	{
		print_them_all(GLOB->ants);
		break ;
	}
	ft_free_struct(GLOB, window);
	return (1);
}
