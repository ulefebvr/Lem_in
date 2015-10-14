/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:00:32 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:00:37 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

float	absi(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

float	get_longueur(int x1, int y1, int x2, int y2)
{
	int longueur;

	longueur = 0;
	if (absi(x2 - x1) >= absi(y2 - y1))
		longueur = absi(x2 - x1);
	else
		longueur = absi(y2 - x1);
	return (longueur);
}

void	get_draw_line(sfRenderTexture **t, float *ds, float *xs, float *ys)
{
	float			i;
	float			xy[2];
	sfVertex		vert;
	sfVertexArray	*vertex;

	xy[0] = xs[0] + 0.5;
	xy[1] = ys[0] + 0.5;
	i = get_longueur(xs[0], ys[0], xs[1], ys[1]);
	vertex = sfVertexArray_create();
	while (i > 1)
	{
		vert.position = (sfVector2f){xy[0], xy[1]};
		vert.color = MYGREY;
		sfVertexArray_append(vertex, vert);
		xy[0] = xy[0] + ds[0];
		xy[1] = xy[1] + ds[1];
		i--;
	}
	sfRenderTexture_drawVertexArray(*t, vertex, NULL);
	sfVertexArray_destroy(vertex);
}

void	draw_line(int node_a, int node_b, sfRenderTexture *t)
{
	float x[2];
	float y[2];
	float d[2];
	t_map *map;

	map = get_node_by_num(node_a);
	x[0] = (map->x * GLOB->zoom);
	y[0] = (map->y * GLOB->zoom);
	map = get_node_by_num(node_b);
	x[1] = (map->x * GLOB->zoom);
	y[1] = (map->y * GLOB->zoom);
	get_longueur(x[0], y[0], x[1], y[1]);
	d[0] = (x[1] - x[0]) / get_longueur(x[0], y[0], x[1], y[1]);
	d[1] = (y[1] - y[0]) / get_longueur(x[0], y[0], x[1], y[1]);
	get_draw_line(&t, d, x, y);
}
