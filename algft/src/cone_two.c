/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:40:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 17:48:59 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_cone	ft_cone(void)
{
	t_cone	c;

	c.min = -0.5;
	c.max = 0.5;
	c.transform = ft_iden_matrix(4, 4);
	c.org = ft_point(0, 0, 0);
	c.r = 1.0;
	c.mat = ft_materials();
	c.closed = true;
	return (c);
}

t_inter	ft_intersection_cone(float a, t_cone c)
{
	t_inter	b;

	b.t = a;
	b.obj.co = c;
	b.obj.c = 'o';
	return (b);
}

t_tuple	ft_normal_at_cone(t_cone c, t_tuple p)
{
	float	dist;

	(void) c;
	p = ft_mult_matrix_tup(ft_inver_matrix(c.transform), p);
	dist = powf(p.x, 2.0) + powf(p.z, 2.0);
	if (dist < 1 && (p.y >= (c.max - EPSILON)))
		return (ft_mult_matrix_tup(ft_trans_matrix(ft_inver_matrix(
						c.transform)), ft_vector(0, 1, 0)));
	if (dist < 1 && (p.y <= (c.min + EPSILON)))
		return (ft_mult_matrix_tup(ft_trans_matrix(
					ft_inver_matrix(c.transform)), ft_vector(0, -1, 0)));
	dist = sqrt(dist);
	if (p.y > 0)
		dist *= -1;
	return (ft_mult_matrix_tup(ft_trans_matrix(ft_inver_matrix(c.transform)),
			ft_vector(p.x, dist, p.z)));
}
