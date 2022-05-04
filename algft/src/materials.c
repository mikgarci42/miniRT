/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:05:44 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 19:30:03 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_bi
{
	float	rde;
	float	ldn;
	float	factor;
}	t_bi;

typedef struct s_col
{
	t_color	color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_tuple	lightv;
	t_tuple	reflectv;
}	t_col;

t_material	ft_materials(void)
{
	t_material	m;

	m.ispattern = false;
	m.color = ft_color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.reflective = 0;
	m.shininess = 200;
	return (m);
}

bool	ft_is_shadowed(t_world w, t_tuple p, int li)
{
	t_tuple		v;
	float		d;
	t_ray		r;
	t_arr_inter	x;
	float		h;

	v = ft_sub_tup(w.light[li].pos, p);
	d = ft_mag_vec(v);
	v = ft_norm_vec(v);
	r = ft_ray(p, v);
	x = ft_inter_world(w, r);
	h = ft_hit(x);
	if (x.count)
		free(x.a);
	if (h > 0 && h < d)
		return (true);
	return (false);
}

t_color	ft_lighting(t_material m, t_light l, t_comps c, bool a)
{
	t_bi	w;
	t_col	z;

	z.color = ft_mult_color(m.color, l.i);
	z.lightv = ft_norm_vec(ft_sub_tup(l.pos, c.op));
	z.ambient = ft_escal_color(z.color, m.ambient);
	w.ldn = ft_dot_prod(z.lightv, c.norm);
	if (w.ldn < 0 || a)
		return (ft_add_color(ft_add_color(z.ambient,
					ft_color(0, 0, 0)), ft_color(0, 0, 0)));
	else
	{
		z.diffuse = ft_escal_color(ft_escal_color(z.color, m.diffuse), w.ldn);
		z.reflectv = ft_reflect(ft_neg_tup(z.lightv), c.norm);
		w.rde = ft_dot_prod(z.reflectv, c.eye);
		if (w.rde <= 0)
			z.specular = ft_color(0, 0, 0);
		else
		{
			w.factor = powf(w.rde, m.shininess);
			z.specular = ft_escal_color(
					ft_escal_color(l.i, m.specular), w.factor);
		}
	}
	return (ft_add_color(ft_add_color(z.ambient, z.diffuse), z.specular));
}
