/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:45:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/23 19:58:30 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdlib.h>
#include <stdio.h>

t_world	ft_def_world(void)
{
	t_world	w;

	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	w.s1 = ft_sphere(ft_point(0, 0, 0), 1.0);
	w.s1.mat.color = ft_color(0.8, 1.0, 0.6);
	w.s1.mat.diffuse = 0.7;
	w.s1.mat.specular = 0.2;
	w.s2 = ft_sphere(ft_point(0, 0, 0), 1.0);
	w.s2.transform = ft_scal_matrix(0.5, 0.5, 0.5);
	return (w);
}

t_arr_inter	ft_add_inter(t_arr_inter temp, t_arr_inter x)
{
	t_arr_inter	a;
	int			i;
	int			j;

	a.count = 0;
	a.a = NULL;
	a.a = malloc(sizeof(t_inter) * (x.count + temp.count));
	i = 0;
	while (i < x.count)
	{
		a.a[i].t = x.a[i].t;
		a.a[i].obj = x.a[i].obj;
		i++;	
	}
	j = 0;
	while (j < temp.count)
	{
		a.a[i + j].t = temp.a[j].t;
		a.a[i + j].obj = temp.a[j].obj;
		j++;
	}
	a.count = i + j;
	return (a);
}

t_arr_inter	ft_order_inter(t_arr_inter x)
{
	t_inter	a;
	int		i;

	i = 1;
	while (i < x.count)
	{
		if (x.a[i].t < x.a[i - 1].t)
		{
			a.t = x.a[i].t;
			a.obj = x.a[i].obj;
			x.a[i].t = x.a[i - 1].t;
			x.a[i].obj = x.a[i - 1].obj;
			x.a[i - 1].t = a.t;
			x.a[i - 1].obj = a.obj;
			i = 0;
		}
		i++;
	}
	return (x);
}

t_arr_inter	ft_inter_world(t_world w, t_ray r)
{
	t_arr_inter	x;
	t_arr_inter	temp;

	x.count = 0;
	x.a = NULL;
	if (w.s1.c == 's')
		temp =	ft_sphere_inter(r, w.s1);
	if (temp.count)
		x = ft_add_inter(temp, x);
	if (w.s2.c == 's')
		temp =	ft_sphere_inter(r, w.s2);
	if (temp.count)
		x = ft_add_inter(temp, x);
	x = ft_order_inter(x);
	return (x);
}

t_color	ft_shade_hit(t_world w, t_comps comps)
{
	return (ft_lighting(comps.obj.mat, w.light, comps.p, comps.eye, comps.norm));
}
