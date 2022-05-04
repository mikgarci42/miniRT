/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:45:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 18:38:48 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdlib.h>

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
	i = -1;
	while (++i < x.count)
	{
		a.a[i].t = x.a[i].t;
		a.a[i].obj = x.a[i].obj;
	}
	j = -1;
	while (++j < temp.count)
	{
		a.a[i + j].t = temp.a[j].t;
		a.a[i + j].obj = temp.a[j].obj;
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
	i = -1;
	while (++i < w.count)
	{
		if (w.s[i].c == 's')
			temp = ft_sphere_inter(r, w.s[i].s);
		if (w.s[i].c == 'p')
			temp = ft_plane_inter(r, w.s[i].p);
		if (w.s[i].c == 'c')
			temp = ft_cylinder_inter(r, w.s[i].cy);
		if (w.s[i].c == 'o')
			temp = ft_cone_inter(r, w.s[i].co);
		if (temp.count)
		{
			x = ft_add_inter(temp, x);
			free(temp.a);
		}
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
	if (comps.obj.c == 'o')
	{
		if (comps.obj.co.mat.reflective == 0.0)
			return (ft_color(0, 0, 0));
		ref = comps.obj.co.mat.reflective;
	}
	reflect_ray.org = comps.op;
	reflect_ray.dir = comps.reflectv;
	col = ft_color_at(w, reflect_ray, rem -1, li);
	return (ft_escal_color(col, ref));
}
