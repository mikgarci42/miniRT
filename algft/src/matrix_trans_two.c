#include "../inc/algft.h"

t_matrix	ft_shear_matrix(t_tuple b, t_tuple c)
{
	t_matrix	a;

	a = ft_iden_matrix(4, 4);
	a.m[1][0] = b.x;
	a.m[2][0] = b.y;
	a.m[0][1] = b.z;
	a.m[2][1] = c.x;
	a.m[0][2] = c.y;
	a.m[1][2] = c.z;
	return (a);
}
