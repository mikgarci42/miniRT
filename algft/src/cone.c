/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 17:48:59 by mikgarci         ###   ########.fr       */
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

static	bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;
	float	y;

	x = r.org.x + (t * r.dir.x);
	z = r.org.z + (t * r.dir.z);
	y = r.org.y + (t * r.dir.y);
	if ((powf(x, 2.0) + powf(z, 2.0)) <= fabs(y))
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

static void	cone_utils(t_ray r, t_bi *w)
{
	w->a = powf(r.dir.x, 2) - powf(r.dir.y, 2) + powf(r.dir.z, 2);
	w->b = (2 * r.org.x * r.dir.x) - (2 * r.org.y * r.dir.y)
		+ (2 * r.org.z * r.dir.z);
	w->c = powf(r.org.x, 2) - powf(r.org.y, 2) + powf(r.org.z, 2);
}

t_arr_inter	ft_cone_inter(t_ray r, t_cone cy)
{
	t_bi		w;
	t_arr_inter	x;

	r = ft_transform(r, ft_inver_matrix(cy.transform));
	cone_utils(r, &w);
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
