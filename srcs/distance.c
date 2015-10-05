#include <math.h>


double		distance(t_lem *a, t_lem *b)
{
	double dist;

	dist = (double)sqrt( pow((b->coord_x - a->coord_x), 2) + pow((b->coord_y - a->coord_y), 2));
	return (dist);
}
