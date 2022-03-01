/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:48:46 by mikgarci          #+#    #+#             */
/*   Updated: 2022/03/01 18:20:18 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdio.h>

t_camera	ft_camera(int hsize, int vsize, float fov)
{
	t_camera	a;
	float		hv;
	float		asp;

	a.hsize = hsize;
	a.vsize = vsize;
	a.fov = fov;
	a.trans = ft_iden_matrix(4, 4);
	hv = tanf(fov / 2);
	asp = (float) hsize / (float)vsize;
	if (asp >= 1)
	{
		a.hw = hv;
		a.hh = hv / asp;
	}
	else
	{
		a.hw = hv * asp;
		a.hh = hv;
	}
	a.ps = (a.hw * 2) / (float) a.hsize;
	return (a);
}

t_ray	ft_ray_for_pixel(t_camera c, float px, float py)
{
	float	xo;
	float	yo;
	t_tuple	p;
	t_tuple	o;
	t_tuple	d;

	xo = (px + 0.5) * c.ps;
	yo = (py + 0.5) * c.ps;
	p = ft_mult_matrix_tup(ft_inver_matrix(c.trans), ft_point(c.hw - xo, c.hh - yo, -1));
	o = ft_mult_matrix_tup(ft_inver_matrix(c.trans), ft_point(0, 0, 0));
	d = ft_norm_vec(ft_sub_tup(p, o));
	return (ft_ray(o, d));
}

t_image	ft_render(t_camera c, t_world w, t_generic g)
{
	int		y;
	int		x;
	t_ray	r;
	t_color	col;

	y = 0;
	while (y < c.vsize - 1)
	{
		x = 0;
		while (x < x.hsize - 1)
		{
			ray = ft_ray_for_pixel(c, x, y);
			col = ft_color_at(w, r);
			ft_scale(x, y, &g, col);
			x++;
		}
		y++;
	}
}
