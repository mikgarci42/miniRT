/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:45:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/27 17:54:50 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdlib.h>

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
		if (w.s[b.count].c == 'u')
		{
			b.s[b.count].cu = w.s[b.count].cu;
			b.s[b.count].c = 'u';
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
	if (s.c == 'u')
	{
		b.s[b.count].cu = s.cu;
		b.s[b.count].c = 'u';
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
	if (a.a == NULL)
		return (a);
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
	if (x.count > 0)
		free(x.a);
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
			temp = ft_sphere_inter(r, w.s[i].s);
		if (w.s[i].c == 'p')
			temp = ft_plane_inter(r, w.s[i].p);
		if (w.s[i].c == 'c')
			//temp = ft_cylinder_inter(r, w.s[i].cy);
			temp = ft_cylinder_inter(w.s[i].cy, r);
		if (w.s[i].c == 'u')
			temp = ft_cube_inter(r, w.s[i].cu);
		if (w.s[i].c == 'o')
			temp = ft_cone_inter(r, w.s[i].co);
		if (temp.count)
		{
			x = ft_add_inter(temp, x);
			free(temp.a);
		}
		i++;
	}
	x = ft_order_inter(x);
	return (x);
}

t_color	ft_reflected_color(t_world w, t_comps comps, int rem, int li)
{
	float	ref;
	t_ray	reflect_ray;
	t_color	col;

	if (rem <= 0)
		return (ft_color(0, 0, 0));
	if (comps.obj.c == 's')
	{
		if (comps.obj.s.mat.reflective == 0.0)
			return (ft_color(0, 0, 0));
		ref = comps.obj.s.mat.reflective;
	}
	if (comps.obj.c == 'p')
	{
		if (comps.obj.p.mat.reflective == 0.0)
			return (ft_color(0, 0, 0));
		ref = comps.obj.p.mat.reflective;
	}
	if (comps.obj.c == 'c')
	{
		if (comps.obj.cy.mat.reflective == 0.0)
			return (ft_color(0, 0, 0));
		ref = comps.obj.cy.mat.reflective;
	}
	reflect_ray.org = comps.op;
	reflect_ray.dir = comps.reflectv;
	col = ft_color_at(w, reflect_ray, rem -1, li);
	return (ft_escal_color(col, ref));
}

t_color	ft_shade_hit(t_world w, t_comps comps, int rem, int li)
{
	bool	a;
	t_color	reflect;
	t_color	sur;
	t_color	temp;
	int		i;

	sur = ft_color(0, 0, 0);
	i = -1;
	while (++i < li)
	{
		a = ft_is_shadowed(w, comps.op, i);
		if (comps.obj.c == 's')
			temp = ft_lighting(comps.obj.s.mat, w.light[i],
					comps.op, comps.eye, comps.norm, a);
		if (comps.obj.c == 'p')
			temp = ft_lighting(comps.obj.p.mat, w.light[i],
					comps.op, comps.eye, comps.norm, a);
		if (comps.obj.c == 'c')
			temp = ft_lighting(comps.obj.cy.mat, w.light[i],
					comps.op, comps.eye, comps.norm, a);
		sur = ft_add_color(temp, sur);
		reflect = ft_reflected_color(w, comps, rem, li);
	}
	return (ft_add_color(sur, reflect));
}
