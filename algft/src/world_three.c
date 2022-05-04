/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:30:23 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 20:12:15 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <stdlib.h>

static void	add_one(t_world w, t_world *b)
{
	b->count = 0;
	while (b->count < w.count)
	{
		if (w.s[b->count].c == 's')
		{
			b->s[b->count].s = w.s[b->count].s;
			b->s[b->count].c = 's';
		}
		if (w.s[b->count].c == 'p')
		{
			b->s[b->count].p = w.s[b->count].p;
			b->s[b->count].c = 'p';
		}
		if (w.s[b->count].c == 'c')
		{
			b->s[b->count].cy = w.s[b->count].cy;
			b->s[b->count].c = 'c';
		}
		if (w.s[b->count].c == 'o')
		{
			b->s[b->count].co = w.s[b->count].co;
			b->s[b->count].c = 'o';
		}
		b->count++;
	}
}

static void	add_two(t_shape s, t_world *b)
{
	if (s.c == 's')
	{
		b->s[b->count].s = s.s;
		b->s[b->count].c = 's';
	}
	if (s.c == 'p')
	{
		b->s[b->count].p = s.p;
		b->s[b->count].c = 'p';
	}
	if (s.c == 'c')
	{
		b->s[b->count].cy = s.cy;
		b->s[b->count].c = 'c';
	}
	if (s.c == 'o')
	{
		b->s[b->count].co = s.co;
		b->s[b->count].c = 'o';
	}
}

t_world	ft_add_world(t_world w, t_shape s)
{
	t_world	b;

	b.s = malloc(sizeof(t_shape) * (w.count + 1));
	add_one(w, &b);
	add_two(s, &b);
	b.count++;
	b.light = w.light;
	if (w.count)
	{
		free(w.s);
	}
	return (b);
}

t_color	ft_shade_hit(t_world w, t_comps comps, int rem, int li)
{
	bool	a;
	t_color	reflect;
	t_color	sur;
	t_color	temp;
	int		i;

	sur = ft_color(0, 0, 0);
	i = -1;
	while (++i < li)
	{
		a = ft_is_shadowed(w, comps.op, i);
		if (comps.obj.c == 's')
			temp = ft_lighting(comps.obj.s.mat, w.light[i], comps, a);
		if (comps.obj.c == 'p')
			temp = ft_lighting(comps.obj.p.mat, w.light[i], comps, a);
		if (comps.obj.c == 'c')
			temp = ft_lighting(comps.obj.cy.mat, w.light[i], comps, a);
		if (comps.obj.c == 'o')
			temp = ft_lighting(comps.obj.co.mat, w.light[i], comps, a);
		sur = ft_add_color(temp, sur);
		reflect = ft_reflected_color(w, comps, rem, li);
	}
	return (ft_add_color(sur, reflect));
}
