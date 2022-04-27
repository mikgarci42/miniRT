/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:51:25 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/27 18:11:40 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>

t_tuple	ft_normal_at_cylinder(t_cylinder c, t_tuple p)
{
	float	dist;

	dist = powf(p.x, 2.0) + powf(p.z, 2.0);
	if (dist < 1 && (p.y >= (c.max - EPSILON)))
		return (ft_mult_matrix_tup(ft_inver_matrix(c.transform),
				ft_vector(0, 1, 0)));
	if (dist < 1 && (p.y <= (c.min + EPSILON)))
		return (ft_mult_matrix_tup(ft_inver_matrix(c.transform),
				ft_vector(0, -1, 0)));
	return (ft_mult_matrix_tup(ft_inver_matrix(c.transform),
			ft_vector(p.x, 0, p.z)));
}

t_cylinder	ft_cylinder(void)
{
	t_cylinder	c;

	c.min = 0.0;
	c.max = 0.0;
	c.transform = ft_iden_matrix(4, 4);
	c.org = ft_point(0, 0, 0);
	c.r = 1.0;
	c.mat = ft_materials();
	c.closed = true;
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
