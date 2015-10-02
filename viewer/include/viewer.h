#ifndef VIEWER_H
# define VIEWER_H

typedef struct		s_info
{
	int				link[128];
	int				node;
	int				ant;
	int				x;
	int				y;
}					t_info;

typedef struct		s_map
{
	t_info			info;
	struct s_map	*next;
}					t_map;

#endif