/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:05:44 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/16 19:02:07 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>

t_material ft_materials(void)
{
	t_material	m;

	m.color = ft_color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return (m);
}

t_color	ft_lighting(t_material m, t_light l, t_tuple pos, t_tuple eyev, t_tuple normalv)
{
	t_color color;
	t_tuple	lightv;
	t_color	ambient;
	t_color diffuse;
	t_color	specular;
	t_tuple	reflectv;
	float	rde;
	float	ldn;
	float	factor;

	color = ft_mult_color(m.color, l.i);
	lightv = ft_norm_vec(ft_sub_tup(l.pos, pos));
	ambient = ft_escal_color(color, m.ambient);
	ldn = ft_dot_prod(lightv, normalv);
	if (ldn < 0)
		return (ft_add_color(ft_color(0, 0, 0), ft_add_color(ambient, ft_color(0, 0, 0))));
	diffuse = ft_escal_color(ft_escal_color(color, m.diffuse), ldn);
	reflectv = ft_reflect(ft_mult_tup(lightv, -1), normalv);
	rde = ft_dot_prod(reflectv, eyev);
	if (rde <= 0)
		specular = ft_color(0, 0, 0);
	else
	{
		factor = powf(rde, m.shininess);
		specular = ft_escal_color(ft_escal_color(l.i, m.specular), factor);
	}
	return (ft_add_color(ft_add_color(ambient, diffuse), specular));
}
