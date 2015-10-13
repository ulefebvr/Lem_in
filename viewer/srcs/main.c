#include "viewer.h"

#include <stdlib.h>

#include <stdio.h>

void	ft_init(void)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	map->num;
	map->node;
	map->ant;
	map->start;
	map->end;
	map->x;
	map->y;
	map->name;
	map->background;
	map->ant1;
	map->ant2;
	map->max;
	map->sprite;
	map->window;
	map->f_texture;
	map->links;
	map->ants;
	map->next;
}

int main(void)
{
	ft_init();
	parse();
	test_csfml();
	return (0);
}