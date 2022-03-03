/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:11:38 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/03 18:01:14 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdio.h>

t_color	ft_color_at(t_world w, t_ray r)
{
	t_arr_inter	x;
	float		hit;
	t_comps		comps;
	t_color		col;

	x = ft_inter_world(w, r);
	hit = ft_hit(x);
	if (!hit)
		return (ft_color(0, 0, 0));
	comps = ft_prep_comps(x.a[0], r);
	col = ft_shade_hit(w, comps);
	return (col);
}
