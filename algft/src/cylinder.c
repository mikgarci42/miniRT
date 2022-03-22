/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/22 20:28:55 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

t_cylinder	ft_cylinder(void)
{
	t_cylinder	c;

	c.min = 0.0;
	c.max = 2.0;
	c.transform = ft_iden_matrix(4, 4);
	c.org = ft_point(0, 0, 0);
	c.r = 1.0;
	c.mat = ft_materials();
	return (c);
}

t_inter	ft_intersection_cylinder(float a, t_cylinder c)
{
	t_inter	b;

	b.t = a;
	b.obj.cy = c;
	b.obj.c = 'c';
	return (b);
}

static t_arr_inter	cylinder(float b, float a, float dis, t_cylinder cy)
{
	t_arr_inter	x;
	float	i;
	float	j;
	
	x.count = 0;
	x.a = NULL;
	if (dis < 0 || fabs(a) < EPSILON)
		return (x);
	i = ((-1 * b) + sqrtf(dis)) / (2 * a);
	j = ((-1 * b) - sqrtf(dis)) / (2 * a);
	x.count = 2;
	x.a = malloc(sizeof(t_inter) * 2);
	x.a[0] = ft_intersection_cylinder(j, cy);
	x.a[1] = ft_intersection_cylinder(i, cy);
	return (x);
}

t_arr_inter	ft_cylinder_inter(t_ray r, t_cylinder cy)
{
	float		a;
	float		b;
	float		c;
	float		disc;
	
	a = (powf(r.dir.x, 2.0)) + (powf(r.dir.z, 2.0));
	b = (2 * r.org.x * r.dir.x) + (2 * r.org.z * r.dir.z);
	c = powf(r.org.x, 2.0) + powf(r.org.z, 2.0) - 1;
	disc = powf(b, 2.0) - (4.0 * a * c);
	return (cylinder(b, a, disc, cy));
}
