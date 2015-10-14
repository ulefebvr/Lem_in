/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:00:43 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:00:46 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

#include "libft.h"

void	ft_set_key(char *action)
{
	int zoom;

	zoom = ft_global(NULL)->zoom;
	if (!ft_strcmp("plus", action))
		ft_global(NULL)->zoom = zoom + 10 <= 100 ? zoom + 10 : 100;
	else if (!ft_strcmp("minus", action))
		ft_global(NULL)->zoom = zoom - 10 >= 0 ? zoom - 10 : 0;
	if (ft_global(NULL)->zoom == 100 || ft_global(NULL)->zoom == 0)
		return ;
	sfCircleShape_destroy(ft_global(NULL)->circle);
	calc_ant(ft_global(NULL)->ants);
	ft_get_window();
}

void	ft_set_perso(void)
{
	static int j;

	if (j == 0)
	{
		j++;
		ft_global(NULL)->ant1 = (void *)SFTCFF("rsrc/img/ant1.png", NULL);
		ft_global(NULL)->ant2 = (void *)SFTCFF("rsrc/img/ant2.png", NULL);
	}
	else if (j == 1)
	{
		j++;
		ft_global(NULL)->ant1 = (void *)SFTCFF("rsrc/img/sacha1.png", NULL);
		ft_global(NULL)->ant2 = (void *)SFTCFF("rsrc/img/sacha2.png", NULL);
	}
	else if (j == 2)
	{
		j = 0;
		ft_global(NULL)->ant1 = (void *)SFTCFF("rsrc/img/fb1.png", NULL);
		ft_global(NULL)->ant2 = (void *)SFTCFF("rsrc/img/fb2.png", NULL);
	}
}

void	get_event(sfRenderWindow *window)
{
	sfEvent e;

	if (sfRenderWindow_pollEvent(window, &e))
	{
		if (e.type == sfEvtClosed || ((e.type == sfEvtKeyPressed) && \
			(e.key.code == sfKeyEscape)))
		{
			sfRenderWindow_close(window);
			ft_free_struct(ft_global(NULL), ft_global(NULL)->window);
			exit(0);
		}
		else if ((e.type == sfEvtKeyPressed) && (e.key.code == sfKeySpace))
			ft_set_perso();
		else if ((e.type == sfEvtKeyPressed) && (e.key.code == sfKeyAdd))
			ft_set_key("plus");
		else if ((e.type == sfEvtKeyPressed) && (e.key.code == sfKeySubtract))
			ft_set_key("minus");
	}
}
