/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:08:22 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/08 20:25:27 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>

t_ray	ft_ray(t_tuple a, t_tuple b)
{
	t_ray	c;

	c.org = ft_point(a.x, a.y, a.z);
	c.dir = ft_vector(b.x, b.y, b.z);
	return (c);
}

t_tuple	ft_pos_ray(t_ray a, float t)
{
	t_tuple	c;

	c = ft_mult_tup(a.dir, t);
	return(ft_add_tup(c, a.org));
}


float	ft_sphere_inter(t_ray r, t_sphere s)
{
	float	a;
	float	b;
	float	c;
	t_tuple	str;
	float	dis;
	
	str = ft_sub_tup(r.org, s.org);
	a = ft_dot_prod(r.dir, r.dir);
	b = 2 * ft_dot_prod(r.dir, str);
	c = ft_dot_prod(str, str) - 1;
	dis = powf(b, 2.0) - (4 * a * c);
	return ((-1 * b + sqrtf(dis)) / (2 * a));
}
