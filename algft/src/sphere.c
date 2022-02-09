/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:22:37 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/09 20:46:21 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

t_sphere	ft_sphere(t_tuple org, float r)
{
	t_sphere	a;

	a.c = 's';
	a.r = r;
	a.org = ft_point(org.x, org.y, org.z);
	return (a);
}	

static t_arr_inter	sphere(float b, float a, float dis, t_sphere s)
{
	t_arr_inter	x;
	float	i;
	float	j;
	
	x.count = 0;
	x.a = NULL;
	if (!dis)
		return (x);
	i = (-1 * b + sqrtf(dis)) / (2 * a);
	j = (-1 * b - sqrtf(dis)) / (2 * a);
	x.count = 2;
	x.a = malloc(sizeof(t_inter) * 2);
	x.a[0].t = j;
	x.a[0].obj = s;
	x.a[1].t = i;
	x.a[1].obj = s;
	return (x);
}

t_arr_inter	ft_sphere_inter(t_ray r, t_sphere s)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	t_tuple	str;
	
	str = ft_sub_tup(r.org, s.org);
	a = ft_dot_prod(r.dir, r.dir);
	b = 2 * ft_dot_prod(r.dir, str);
	c = ft_dot_prod(str, str) - 1;
	dis = powf(b, 2.0) - (4 * a * c);
	return (sphere(b, a, dis, s));
}
