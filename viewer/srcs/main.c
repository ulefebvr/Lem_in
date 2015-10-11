#include "viewer.h"

#include <stdlib.h>

#include <stdio.h>

int main(void)
{
	t_map *map;

	parse();
	test_csfml();
	map = ft_global(NULL);
	return (0);
}