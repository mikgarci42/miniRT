/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/05 20:41:05 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

typedef struct s_bi {
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_bi;

t_cone	ft_cone(void)
{
	t_cone	c;

	c.min = -5.0;
	c.max = 5.0;
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
	float	i;
	float	j;
	float	ii;
	float	jj;
	
	(void) r;
	i = ((-1 * w.b) + sqrtf(w.disc)) / (2 * w.a);
	ii = r.org.y + (i * r.dir.y);
	if (cy.min < ii && ii < cy.max)
	{
		x.a[x.count] = ft_intersection_cone(i, cy);
		x.count++;
	}
	j = ((-1 * w.b) - sqrtf(w.disc)) / (2 * w.a);
	jj = r.org.y + (j * r.dir.y);
	if (cy.min < jj && jj < cy.max)
	{
		x.a[x.count] = ft_intersection_cone(j, cy);
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
	
	
	r = ft_transform(r, ft_inver_matrix(cy.transform));
	w.a = powf(r.dir.x, 2) - powf(r.dir.y, 2) + powf(r.dir.z, 2);
	w.b = (2 * r.org.x * r.dir.x) - (2 * r.org.y * r.dir.y) + (2 * r.org.z * r.dir.z);
	w.c = powf(r.org.x, 2) - powf(r.org.y, 2) + powf(r.org.z, 2);
	w.disc = powf(w.b, 2.0) - (4.0 * w.a * w.c);
	x.count = 0;
	x.a = NULL;
	if (w.disc < 0 || (fabs(w.a) < EPSILON && fabs(w.b) < EPSILON))
		return (x);
	x.a = malloc(sizeof(t_inter) * 2);
	if (fabs(w.a) < EPSILON)
	{
		//x = intersect_caps(cy, r, x);
		//if (!x.count)
			//free(x.a);
		x.a[0].t = (-1 * w.c) / (2 * w.b);
		x.count = 1;
		return (x);
	}
	return (cone(w, cy, x, r));
}

t_tuple	ft_normal_at_cone(t_cone c, t_tuple p)
{
	(void) c;
	float	dist;

	dist = powf(p.x, 2.0) + powf(p.z, 2.0);
	if (dist < 1 && (p.y >= (c.max - EPSILON)))
		return (ft_vector(0, 1, 0));
	if (dist < 1 && (p.y <= (c.min + EPSILON)))
		return (ft_vector(0, -1, 0));
	return (ft_vector(p.x, 0, p.z));
}
