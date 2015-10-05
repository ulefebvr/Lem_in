#ifndef VIEWER_H
# define VIEWER_H

typedef struct		s_map
{
	int				link[128];
	int				node;
	int				ant;
	int				start;
	int				end;
	int				x;
	int				y;
	char			*name;
	struct s_map	*next;
}					t_map;

// ft_global.c
t_map				*ft_global(t_map *map);

// read.c
int					parse(void);

// print.c
int					test_csfml(void);

// lst.c
int					lst_add(char **info, int *comment);

// Compilation:
// gcc srcs/* -I include -I libft/includes libft/libft.a -I ~/.brew/include -L ~/.brew/lib -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$HOME/.brew/lib

#endif