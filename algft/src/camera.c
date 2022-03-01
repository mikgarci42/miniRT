/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:48:46 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/23 20:52:34 by mikgarci         ###   ########.fr       */
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

}
