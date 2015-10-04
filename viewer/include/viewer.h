#ifndef VIEWER_H
# define VIEWER_H

typedef struct		s_info
{
	int				link[128];
	int				node;
	int				ant;
	int				start;
	int				end;
	int				x;
	int				y;
}					t_info;

typedef struct		s_map
{
	t_info			info;
	struct s_map	*next;
}					t_map;

t_map				*ft_global(t_map *map);
int					test_csfml(void);

#endif