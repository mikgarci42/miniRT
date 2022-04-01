/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:45:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/01 20:17:46 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdlib.h>

/*t_world	ft_def_world(void)
{
	t_world	w;
	t_sphere s1;
	t_sphere s2;

	w.count = 0;
	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	s1 = ft_sphere(ft_point(0, 0, 0), 1.0);
	s1.mat.color = ft_color(0.8, 1.0, 0.6);
	s1.mat.diffuse = 0.7;
	s1.mat.specular = 0.2;
	w = ft_add_world(w, s1);
	s2 = ft_sphere(ft_point(0, 0, 0), 1.0);
	s2.transform = ft_scal_matrix(0.5, 0.5, 0.5);
	w = ft_add_world(w, s2);
	return (w);
}*/

t_world	ft_add_world(t_world w, t_shape s)
{
	t_world	b;

	b.s = malloc(sizeof(t_shape) * (w.count + 1));
	b.count = 0;
	while (b.count < w.count)
	{
		if (w.s[b.count].c == 's')
		{
			b.s[b.count].s = w.s[b.count].s;
			b.s[b.count].c = 's';
		}
		if (w.s[b.count].c == 'p')
		{
			b.s[b.count].p = w.s[b.count].p;
			b.s[b.count].c = 'p';
		}
		if (w.s[b.count].c == 'c')
		{
			b.s[b.count].cy = w.s[b.count].cy;
			b.s[b.count].c = 'c';
		}
		b.count++;
	}
	if (s.c == 's')
	{
		b.s[b.count].s = s.s;
		b.s[b.count].c = 's';
	}
	if (s.c == 'p')
	{
		b.s[b.count].p = s.p;
		b.s[b.count].c = 'p';
	}
	if (s.c == 'c')
	{
		b.s[b.count].cy = s.cy;
		b.s[b.count].c = 'c';
	}
	b.count++;
	b.light = w.light;
	if (w.count)
	{
		free(w.s);
	}
	return (b);
}

t_arr_inter	ft_add_inter(t_arr_inter temp, t_arr_inter x)
{
	t_arr_inter	a;
	int			i;
	int			j;

	a.count = 0;
	a.a = NULL;
	a.a = malloc(sizeof(t_inter) * (x.count + temp.count + 1));
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
	int			i;

	x.count = 0;
	x.a = NULL;
	i = 0;
	while (i < w.count)
	{

		if (w.s[i].c == 's')
			temp =	ft_sphere_inter(r, w.s[i].s);
		if (w.s[i].c == 'p')
			temp =	ft_plane_inter(r, w.s[i].p);
		if (w.s[i].c == 'c')
			temp =	ft_cylinder_inter(r, w.s[i].cy);
		if (temp.count)
			x = ft_add_inter(temp, x);
		i++;
	}
	x = ft_order_inter(x);
	return (x);
}

t_color	ft_shade_hit(t_world w, t_comps comps)
{
	bool	a;

	a = ft_is_shadowed(w, comps.op);
	if (comps.obj.c == 's')
		return (ft_lighting(comps.obj.s.mat, w.light, comps.p, comps.eye, comps.norm, a));
	if (comps.obj.c == 'p')
		return (ft_lighting(comps.obj.p.mat, w.light, comps.p, comps.eye, comps.norm, a));
	if (comps.obj.c == 'c')
		return (ft_lighting(comps.obj.cy.mat, w.light, comps.p, comps.eye, comps.norm, a));
	return (ft_color(0, 0, 0));
}
