/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/26 17:48:42 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_bi {
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_bi;

t_cone	ft_cone(void)
{
	t_cone	c;

	c.min = -0.5;
	c.max = 0.5;
	c.transform = ft_iden_matrix(4, 4);
	c.org = ft_point(0, 0, 0);
	c.r = 1.0;
	c.mat = ft_materials();
	c.closed = true;
	return (c);
}

t_inter	ft_intersection_cone(float a, t_cone c)
{
	t_inter	b;

	b.t = a;
	b.obj.co = c;
	b.obj.c = 'o';
	return (b);
}

static	bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.org.x + (t * r.dir.x);
	z = r.org.z + (t * r.dir.z);
	if ((powf(x, 2.0) + powf(z, 2.0)) <= 1)
		return (true);
	return (false);
}

static t_arr_inter	intersect_caps(t_cone cy, t_ray r, t_arr_inter x)
{
	float	t;

	if (!cy.closed || fabs(r.dir.y) < EPSILON)
		return (x);
	t = (cy.min - r.org.y) / r.dir.y;
	if (check_cap(r, t))
	{
		x.a[x.count] = ft_intersection_cone(t, cy);
		x.count++;
	}
	t = (cy.max - r.org.y) / r.dir.y;
	if (check_cap(r, t))
	{
		x.a[x.count] = ft_intersection_cone(t, cy);
		x.count++;
	}
	return (x);
}

static t_arr_inter	cone(t_bi w, t_cone cy, t_arr_inter x, t_ray r)
{
	float	sqrtdisc;
	float	t0;
	float	t1;
	float	y0;
	float	y1;

	sqrtdisc = sqrtf(w.disc);
	t0 = (-w.b - sqrtdisc) / (2.0 * w.a);
	t1 = (-w.b + sqrtdisc) / (2.0 * w.a);
	y0 = r.org.y + (t0 * r.dir.y);
	if (cy.min < y0 && y0 < cy.max)
	{
		x.a[x.count] = ft_intersection_cone(t0, cy);
		x.count++;
	}
	y1 = r.org.y + (t1 * r.dir.y);
	if (cy.min < y1 && y1 < cy.max)
	{
		x.a[x.count] = ft_intersection_cone(t1, cy);
		x.count++;
	}
	x = intersect_caps(cy, r, x);
	if (!x.count)
		free(x.a);
	return (x);
}

t_arr_inter	ft_cone_inter(t_ray r, t_cone cy)
{
	t_bi		w;
	t_arr_inter	x;

	w.a = powf(r.dir.x, 2) - powf(r.dir.y, 2) + powf(r.dir.z, 2);
	w.b = (2 * r.org.x * r.dir.x) - (2 * r.org.y * r.dir.y)
		+ (2 * r.org.z * r.dir.z);
	w.c = powf(r.org.x, 2) - powf(r.org.y, 2) + powf(r.org.z, 2);
	x.count = 0;
	x.a = NULL;
	if (fabs(w.a) < EPSILON && fabs(w.b) > EPSILON)
	{
		x.a = malloc(sizeof(t_inter) * 4);
		x.a[0] = ft_intersection_cone((-1 * w.c) / (2 * w.b), cy);
		x.count = 1;
		x = intersect_caps(cy, r, x);
		return (x);
	}
	if (fabs(w.a) < EPSILON)
		return (x);
	w.disc = powf(w.b, 2.0) - (4.0 * w.a * w.c);
	if (fabs(w.disc) < EPSILON)
		w.disc = 0;
	if (w.disc < 0)
		return (x);
	x.a = malloc(sizeof(t_inter) * 4);
	return (cone(w, cy, x, r));
}

t_tuple	ft_normal_at_cone(t_cone c, t_tuple p)
{
	float	dist;

	(void) c;
	dist = powf(p.x, 2.0) + powf(p.z, 2.0);
	if (dist < 1 && (p.y >= (c.max - EPSILON)))
		return (ft_vector(0, 1, 0));
	if (dist < 1 && (p.y <= (c.min + EPSILON)))
		return (ft_vector(0, -1, 0));
	return (ft_vector(p.x, 0, p.z));
}
