/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:39:54 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/29 18:29:09 by migarcia         ###   ########.fr       */
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

static t_arr_inter	intersect_caps(t_cylinder cy, t_ray r, t_arr_inter x)
{
	float	t;

	if (!cy.closed || fabs(r.dir.y) < EPSILON)
		return (x);
	t = (cy.min - r.org.y) / r.dir.y;
	if (check_cap(r, t))
	{
		x.a[x.count] = ft_intersection_cylinder(t, cy);
		x.count++;
	}
	t = (cy.max - r.org.y) / r.dir.y;
	if (check_cap(r, t))
	{
		x.a[x.count] = ft_intersection_cylinder(t, cy);
		x.count++;
	}
	return (x);
}

static t_arr_inter	cylinder(t_bi w, t_cylinder cy, t_arr_inter x, t_ray r)
{
	float	i;
	float	j;
	float	ii;
	float	jj;

	(void) r;
	i = ((-1 * w.b) - sqrtf(w.disc)) / (2 * w.a);
	ii = r.org.y + (i * r.dir.y);
	if (cy.min < ii && ii < cy.max)
	{
		x.a[x.count] = ft_intersection_cylinder(i, cy);
		x.count++;
	}
	j = ((-1 * w.b) + sqrtf(w.disc)) / (2 * w.a);
	jj = r.org.y + (j * r.dir.y);
	if (cy.min < jj && jj < cy.max)
	{
		x.a[x.count] = ft_intersection_cylinder(j, cy);
		x.count++;
	}
	x = intersect_caps(cy, r, x);
	if (!x.count)
		free(x.a);
	return (x);
}

t_arr_inter	ft_cylinder_inter(t_ray r, t_cylinder cy)
{
	t_bi		w;
	t_arr_inter	x;

	r = ft_transform(r, ft_inver_matrix(cy.transform));
	w.a = (powf(r.dir.x, 2.0)) + (powf(r.dir.z, 2.0));
	w.b = (2 * r.org.x * r.dir.x) + (2 * r.org.z * r.dir.z);
	w.c = powf(r.org.x, 2.0) + powf(r.org.z, 2.0) - 1;
	w.disc = powf(w.b, 2.0) - (4.0 * w.a * w.c);
	x.count = 0;
	x.a = NULL;
	x.a = malloc(sizeof(t_inter) * 2);
	if (w.disc < 0 || fabs(w.a) < EPSILON)
	{
		x = intersect_caps(cy, r, x);
		if (!x.count)
			free(x.a);
		return (x);
	}
	return (cylinder(w, cy, x, r));
}

int	ft_is_between(float min, float max, float val)
{
	if (min < val && val < max)
		return (1);
	else
		return (0);
}

t_arr_inter	ft_void_inter(void)
{
	t_arr_inter	inter;

	inter.count = 0;
	inter.a = NULL;
	return (inter);
}

int	ft_check_cap(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.org.x + t * ray.dir.x;
	z = ray.org.z + t * ray.dir.z;
	if ((powf(x, 2) + powf(z, 2)) <= 1.00001)
		return (1);
	else
		return (0);
}

t_arr_inter	ft_intersect_caps(t_cylinder cyl, t_ray ray, t_arr_inter inter)
{
	float			t;

	if (cyl.closed)
	{
		t = (cyl.min - ray.org.y) / ray.dir.y;
		if (ft_check_cap(ray, t))
		{
			inter.a[inter.count] = ft_intersection_cylinder(t, cyl);
			inter.count = inter.count + 1;
		}
		t = (cyl.max - ray.org.y) / ray.dir.y;
		if (ft_check_cap(ray, t))
		{
			inter.a[inter.count] = ft_intersection_cylinder(t, cyl);
			inter.count = inter.count + 1;
		}
	}
	if (inter.count == 0)
	{
		free(inter.a);
		inter.a = NULL;
	}
	return (inter);
}

t_arr_inter	ft_cyl_inter_aux(t_cylinder cyl, t_ray ray, float t0, float t1)
{
	t_arr_inter	inter;
	float			ttemp;

	inter.a = malloc(sizeof(t_inter) * 4);
	if (t0 > t1)
	{
		ttemp = t0;
		t0 = t1;
		t1 = ttemp;
	}
	inter.count = 0;
	if (ft_is_between(cyl.min, cyl.max,
			ray.org.y + t0 * ray.dir.y))
	{
		inter.a[inter.count] = ft_intersection_cylinder(t0, cyl);
		inter.count = inter.count + 1;
	}
	if (ft_is_between(cyl.min, cyl.max,
			ray.org.y + t1 * ray.dir.y))
	{
		inter.a[inter.count] = ft_intersection_cylinder(t1, cyl);
		inter.count = inter.count + 1;
	}
	return (ft_intersect_caps(cyl, ray, inter));
}

t_arr_inter	ft_cylinder_inter1(t_cylinder cyl, t_ray ray)
{
	t_arr_inter	inter;
	float			a;
	float			b;
	float			c;
	float			disc;

	ray = ft_transform(ray, ft_inver_matrix(cyl.transform));
	inter.a = malloc(sizeof(t_inter) * 4);
	a = powf(ray.dir.x, 2) + powf(ray.dir.z, 2);
	if (a < 0.00001 && a > 0.00001)
		return (ft_intersect_caps(cyl, ray, inter));
	b = 2 * ray.org.x * ray.dir.x
		+ 2 * ray.org.z * ray.dir.z;
	c = powf(ray.org.x, 2) + powf(ray.org.z, 2) - 1;
	disc = pow(b, 2) - 4 * a * c;
	free(inter.a);
	if (disc < 0)
		return (ft_void_inter());
	else
		inter = ft_cyl_inter_aux(cyl, ray, (b * -1 - sqrtf(disc)) / (2 * a),
				(b * -1 + sqrtf(disc)) / (2 * a));
	return (inter);
}
