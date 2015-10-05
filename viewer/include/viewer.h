#ifndef VIEWER_H
# define VIEWER_H

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
	t_links			*links;
	struct s_map	*next;
}					t_map;

// ft_global.c
t_map				*ft_global(t_map *map);

// parse.c
int					parse(void);

// parse_link.c
int					check_link(char *line);
char				**is_link(char *line);

// lst.c
int					lst_add(char **info, int *comment);
int					lst_add_link(char **link);

// print.c
int					test_csfml(void);

// Compilation:
// gcc srcs/* -I include -I libft/includes libft/libft.a -I ~/.brew/include -L ~/.brew/lib -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$HOME/.brew/lib

#endif