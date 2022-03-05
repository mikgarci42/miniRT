/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:29:02 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/01 19:51:48 by mikgarci         ###   ########.fr       */
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
	comps.norm = ft_normal_at(comps.obj, comps.p);
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
