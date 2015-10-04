#include "viewer.h"

#include "libft.h"
#include <stdlib.h>

#include "stdio.h"

int	lst_add(char **info, int *comment)
{
	t_map *new;
	t_map *begin;
	
	begin = ft_global(NULL);
	new = (t_map *)malloc(sizeof(t_map));
	new->start = comment[0];
	new->end = comment[1];
	new->name = ft_strdup(info[0]);
	new->x = ft_atoi(info[1]);
	new->y = ft_atoi(info[2]);
	new->next = NULL;
	ft_freetab(info);
	if (!begin)
		ft_global(new);
	else
	{
		while(begin->next)
			begin = begin->next;
		begin->next = new;
	}
	return (1);
}