/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:24:38 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/22 19:57:18 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

t_plane	ft_plane(void)
{
	t_plane	a;

	a.transform = ft_iden_matrix(4, 4);
	a.org = ft_point(0, 0, 0);
	a.norm = ft_vector(0, 1, 0);
	a.mat = ft_materials();
	return (a);
}	

t_tuple	ft_normal_at_plane(t_plane plane, t_tuple p)
{
	t_tuple a;
	t_tuple	b;
	t_tuple c;

	a = ft_mult_matrix_tup(ft_inver_matrix(plane.transform), p);
	b = ft_sub_tup(a, plane.org);
	c = ft_mult_matrix_tup(ft_trans_matrix(ft_inver_matrix(plane.transform)), b);
	c.w = 0;
	return (ft_vector(0, 1, 0));
}

t_inter	ft_intersection_plane(float a, t_plane p)
{
	t_inter	b;

	b.t = a;
	b.obj.p = p;
	b.obj.c = 'p';
	return (b);
}

t_arr_inter	ft_plane_inter(t_ray r, t_plane p)
{
	t_arr_inter	x;
	t_tuple		a;
	float		b;
	float		c;
	float		t;
	
	c = ft_dot_prod(r.dir, p.norm);
	x.count = 0;
	x.a = NULL;
	if (fabs(c) < EPSILON)
		return (x);
	x.count = 1;
	a = ft_sub_tup(p.org, r.org);
	b = ft_dot_prod(a, p.norm);
	t = b / c;
	x.a = malloc(sizeof(t_inter));
	x.a[0] = ft_intersection_plane(t, p);
	return (x);
}

t_tuple	ft_normal_at_cylinder(t_cylinder c, t_tuple p)
{
	(void) c;
	return (ft_vector(p.x, 0, p.z));
}
