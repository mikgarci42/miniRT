/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:29:02 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/11 20:09:26 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"

t_comps	ft_prep_comps(t_inter i, t_ray r)
{
	t_comps	comps;

	comps.t = i.t;
	comps.obj = i.obj;
	comps.p = ft_pos_ray(r, comps.t);
	comps.eye = ft_mult_tup(r.dir, -1.0);
	if (comps.obj.c == 's')
		comps.norm = ft_normal_at(comps.obj.s, comps.p);
	if (comps.obj.c == 'p')
		comps.norm = ft_normal_at_plane(comps.obj.p, comps.p);
	if (comps.obj.c == 'c')
		comps.norm = ft_normal_at_cylinder(comps.obj.cy, comps.p);
	if (comps.obj.c == 'o')
		comps.norm = ft_normal_at_cone(comps.obj.co, comps.p);
	if (comps.obj.c == 'u')
		comps.norm = ft_normal_at_cube(comps.obj.cu, comps.p);
	comps.op = ft_add_tup(comps.p, ft_mult_tup(comps.norm, EPSILON));
	if (ft_dot_prod(comps.norm, comps.eye) < 0)
	{
		comps.inside = true;
		comps.norm = ft_mult_tup(comps.norm, -1.0);
	}
	else
		comps.inside = false;
	return (comps);
}
