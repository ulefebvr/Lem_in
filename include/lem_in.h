/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:32:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/04 19:58:41 by ulefebvr         ###   ########.fr       */
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
	struct s_path			*prev;
}							t_path;

typedef struct				s_paths
{
	t_path					*path;
	int						max;
	int						len;
	struct s_paths			*next;
	struct s_paths			*prev;
}							t_paths;

typedef struct				s_info
{
	t_lem					*list;
	t_paths					*paths;
	int						no_ant;
	int						no_path;
	int						error;
	char					*buffer;
}							t_info;

int							ft_tablen(char **tab);
int							ft_digit(char *str);
void						ft_exit(t_info *ret);
int							ft_pathlen(t_path *path);
int							ft_round(float number);

void						ft_freetab(char **tab);
void						free_path(t_path *path);
void						free_paths(t_paths *paths);
void						free_list(t_lem *list);

int							get_links(char *line, t_info *info);
t_lem						*get_room(t_info *info, int inf[4]);
t_info						*ft_parse(void);

t_lem						*get_roomstartend(t_lem *list, int end);

int							pathfinder(t_info *info);
t_path						*get_path(t_info *info);
t_paths						*get_allpaths(t_info *info, t_paths *prev);

void						set_prorata_len(t_info *info);

void						sendtopath(t_info *info);

#endif