/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:11:38 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/01 19:51:49 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"

t_color	ft_color_at(t_world w, t_ray r)
{
	t_arr_inter	x;
	float		hit;
	t_comps		comps;

	x = ft_inter_world(w, r);
	hit = ft_hit(x);
	if (!hit)
		return (ft_color(0, 0, 0));
	comps = ft_prep_comps(x.a[0], r);
	return (ft_shade_hit(w, comps));
}