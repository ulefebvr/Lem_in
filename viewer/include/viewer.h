/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:02:35 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/14 23:02:37 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include "SFML/Graphics.h"

# define ZOOM		60
# define HEIGHT		2000
# define WIDTH		2000
# define SPEED		50000

/*
** Colors
*/
# define MYBROWN	(sfColor){51, 36, 22, 255}
# define MYGREY		(sfColor){150, 150, 150, 255}
# define MYYELLOW	(sfColor){189, 181, 9, 255}
# define MYGREEN	(sfColor){9, 189, 89, 255}
# define MYBLUE		(sfColor){9, 157, 179, 255}
# define MYRED		(sfColor){189, 24, 9, 255}

# define SFTCFF		sfTexture_createFromFile
# define GLOB		ft_global(NULL)

typedef struct		s_ants
{
	int				lap;
	int				ant_num;
	int				start;
	int				step;
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			longueur;
	float			i;
	struct s_ants	*next;
	struct s_ants	*prev;
}					t_ants;

typedef struct		s_links
{
	int				node;
	struct s_links	*next;
}					t_links;

typedef struct		s_map
{
	int				num;
	int				node;
	int				ant;
	int				start;
	int				end;
	int				x;
	int				y;
	char			*name;
	void			*background;
	void			*ant1;
	void			*ant2;
	int				max;
	void			*sprite;
	void			*window;
	void			*f_texture;
	void			*circle;
	int				zoom;
	int				node_size;
	t_links			*links;
	t_ants			*ants;
	struct s_map	*next;
}					t_map;

/*
** ft_global.c
*/
t_map				*ft_global(t_map *map);

/*
** parse.c
*/
int					parse(void);
int					check_node(char *line);

/*
** parse_link.c
*/
int					check_link(char *line);
char				**is_link(char *line);

/*
** parse_ant.c
*/
int					check_ant(char *line);

/*
** lst.c
*/
int					lst_add(char **info, int *comment);
int					lst_add_link(char **link);
int					lst_add_ant(char **ants, int lap);

/*
** get_elem.c
*/
int					get_ant_last_step(int ant_num);
int					get_node_num(char *name);
int					get_node_stat(char *stat);
t_map				*get_node_by_num(int num);

/*
** print.c
*/
int					print_all(void);
int					ft_get_window(void);
void				calc_ant(t_ants *ants);

/*
**  print_ants.c
*/
int					is_on_good_way(int node);
void				print_them_all(t_ants *list);

/*
** draw_line.c
*/
float				absi(float i);
void				draw_line(int node_a, int node_b, sfRenderTexture *texture);

/*
** event.c
*/
void				ft_set_key(char *action);
void				ft_set_perso();
void				get_event(sfRenderWindow *window);

/*
** free.c
*/

void				ft_free_struct(t_map *map, sfRenderWindow *window);

// Compilation:
// gcc srcs/* -I include -I libft/includes libft/libft.a -I ~/.brew/include -L ~/.brew/lib -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$HOME/.brew/lib

#endif
