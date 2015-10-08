/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 10:12:58 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/08 14:33:31 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <math.h>

double		distance(t_lem *a, t_lem *b)
{
	double	dist;

	dist = (double)sqrt(pow((b->coord_x - a->coord_x), 2)
		+ pow((b->coord_y - a->coord_y), 2));
	return (dist);
}

int			ft_round(float number)
{
	int		rounder;

	rounder = (int)((number - (int)number) * 10);
	return (rounder >= 5 ? (int)number + 1 : (int)number);
}
