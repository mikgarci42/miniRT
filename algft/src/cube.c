/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/20 17:55:21 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

typedef struct 	s_minmax{
	float	*x;
	float	*y;
	float	*z;
}	t_minmax;

t_cube	ft_cube(void)
{
	t_cube	c;

	c.transform = ft_iden_matrix(4, 4);
	c.org = ft_point(0, 0, 0);
	c.mat = ft_materials();
	return (c);
}

t_inter	ft_intersection_cube(float a, t_cube c)
{
	t_inter	b;

	b.t = a;
	b.obj.cu = c;
	b.obj.c = 'u';
	return (b);
}

static float	*check_axis(float o, float d)
{
	float	tmin_n;
	float	tmax_n;
	float	*t;

	t = malloc(2 * sizeof(float));
	tmin_n = -1.0 - o;
	tmax_n = 1.0 - o;
	if (fabs(d) >= EPSILON)
	{
		t[0] = tmin_n / d;
		t[1] = tmax_n / d;
	}
	else
	{
		t[0] = tmin_n * (-1 * (log(0)));
		t[1] = tmax_n * (-1 * log(0));
	}
	if (t[0] > t[1])
	{
		tmin_n = t[0];
		t[0] = t[1];
		t[1] = tmin_n;
	}
	return (t);
}

t_arr_inter	ft_cube_inter(t_ray r, t_cube cu)
{
	t_minmax	t;
	float		tmin;
	float		tmax;
	t_arr_inter	x;

	x.count = 0;
	x.a = NULL;
	t.x = check_axis(r.org.x, r.dir.x);
	t.y = check_axis(r.org.y, r.dir.y);
	t.z = check_axis(r.org.z, r.dir.z);
	tmin = fmax(t.x[0], fmax(t.y[0], t.z[0]));
	tmax = fmin(t.x[1], fmin(t.y[1], t.z[1]));
	free(t.x);
	free(t.z);
	free(t.y);
	if (tmin > tmax)
		return (x);
	x.count = 2;
	x.a = malloc(2 * sizeof(t_inter));
	x.a[0] = ft_intersection_cube(tmin, cu);
	x.a[1] = ft_intersection_cube(tmax, cu);
	return (x);
}

t_tuple	ft_normal_at_cube(t_cube c, t_tuple p)
{
	float	maxc;

	(void) c;
	maxc = fmax(fabs(p.x), fmax(fabs(p.y), fabs(p.z)));
	if (maxc == fabs(p.x))
		return (ft_vector(p.x, 0, 0));
	if (maxc == fabs(p.y))
		return (ft_vector(0, p.y, 0));
	return (ft_vector(0, 0, p.z));
}
