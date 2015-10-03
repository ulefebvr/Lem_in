/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:32:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/03 17:49:43 by ulefebvr         ###   ########.fr       */
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
	struct s_lem			*path;
	int						dist;
}							t_lem;

typedef struct				s_path
{
	struct s_lem			*room;
	struct s_path			*next;
}							t_path;

typedef struct				s_info
{
	t_lem					*list;
	t_path					*path;
	int						no_ant;
	int						error;
	char					*buffer;
}							t_info;

int							ft_tablen(char **tab);
void						ft_freetab(char **tab);
int							ft_digit(char *str);
void						ft_exit(t_info *ret);

int							get_links(char *line, t_info *info);
t_lem						*get_room(t_info *info, int inf[4]);
t_info						*ft_parse(void);

t_lem						*get_roomstartend(t_lem *list, int end);

int							pathfinder(t_info *info);
t_path						*get_path(t_info *info);

#endif