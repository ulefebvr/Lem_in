#include "viewer.h"

t_map	*ft_global(t_map *map)
{
	static t_map *save;

	if (map)
		save = map;
	return (save);
}
