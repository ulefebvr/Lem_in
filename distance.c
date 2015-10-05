#include <math.h>
#include <stdio.h>

typedef struct				s_lem
{
	int						no;
	char					*name;
	int						ant;
	int						link[128];
	int						start;
	int						end;
	int						stat;
	double					coord_x;
	double					coord_y;
	struct s_lem			*next;
	struct s_lem			*path;
	int						dist;
}							t_lem;

double		distance(t_lem *a, t_lem *b)
{
	double dist;

	dist = (double)sqrt( pow((b->coord_x - a->coord_x), 2) + pow((b->coord_y - a->coord_y), 2));
	return (dist);
}

int		main(void)
{
	t_lem a;
	t_lem b;
	double dist;

	a.coord_x = -12;
	b.coord_x = 21;
	a.coord_y = 7;
	b.coord_y = 48;
	dist = distance(&a, &b);
	printf("%f\n", dist);
	return (0);
}