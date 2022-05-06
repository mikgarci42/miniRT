/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:24:38 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 17:49:52 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
	t_tuple	a;

	(void) p;
	a = ft_mult_matrix_tup(ft_trans_matrix(ft_inver_matrix(plane.transform)),
			ft_vector(0, 1, 0));
	return (a);
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
	float		t;

	r = ft_transform(r, ft_inver_matrix(p.transform));
	if (fabs(r.dir.y) < 0.00001)
	{
		x.count = 0;
		x.a = NULL;
		return (x);
	}
	x.count = 1;
	x.a = malloc(sizeof(t_inter));
	t = (r.org.y * -1) / r.dir.y;
	x.a[0] = ft_intersection_plane(t, p);
	return (x);
}
