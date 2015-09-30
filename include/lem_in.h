/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:32:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 17:39:50 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

typedef struct				s_lem
{
	int						no;
	char					*name;
	int						ant;
	int						link[128];
	int						start;
	int						end;
	int						stat;
	int						coord_x;
	int						coord_y;
	struct s_lem			*next;
}							t_lem;

typedef struct				s_info
{
	t_lem					*list;
	int						no_ant;
}							t_info;

int							ft_tablen(char **tab);
void						ft_freetab(char **tab);

t_info						*ft_parse(void);

#endif