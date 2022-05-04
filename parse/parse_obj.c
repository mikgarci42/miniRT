/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:53:14 by migarcia          #+#    #+#             */
/*   Updated: 2022/05/04 19:17:25 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../algft/inc/algft.h"
#include "../libft/libft.h"
#include "parse.h"
#include <stdio.h>
#include <math.h>

void	ft_parse_trans(t_shape *sp, t_tuple org, float di)
{
	sp->s.transform = ft_mult_matrix(sp->s.transform,
			ft_transla_matrix(org.x, org.y, org.z));
	sp->s.transform = ft_mult_matrix(sp->s.transform,
			ft_scal_matrix(di / 2, di / 2, di / 2));
}

int	ft_parse_sphere(t_scene *scene, char *str)
{
	t_shape	sp;
	t_tuple	org;
	float	di;

	str++;
	str++;
	ft_skipspace(&str);
	org = ft_parse_coor(&str);
	ft_skipspace(&str);
	di = ft_atof(&str);
	sp.c = 's';
	sp.s = ft_sphere();
	ft_skipspace(&str);
	ft_parse_trans(&sp, org, di);
	sp.s.mat.color = ft_get_color(&str);
	scene->world = ft_add_world(scene->world, sp);
	return (0);
}

void	ft_parse_plane_trans(t_shape *pl, t_tuple org, t_tuple dir)
{
	pl->p.transform = ft_mult_matrix(pl->p.transform,
			ft_transla_matrix(org.x, org.y, org.z));
	pl->p.transform = ft_mult_matrix(pl->p.transform,
			ft_rotate_z_matrix(dir.x * M_PI / 2));
	pl->p.transform = ft_mult_matrix(pl->p.transform,
			ft_rotate_x_matrix(dir.z * M_PI / 2));
}

int	ft_parse_plane(t_scene *scene, char *str)
{
	t_shape	pl;
	t_tuple	org;
	t_tuple	dir;

	str++;
	str++;
	ft_skipspace(&str);
	org = ft_parse_coor(&str);
	ft_skipspace(&str);
	dir = ft_parse_coor(&str);
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0 || dir.y > 1.0
		|| dir.z < -1.0 || dir.z > 1.0)
		return (ft_error("Plane 3D vector out of range."));
	dir = ft_norm_vec(dir);
	pl.c = 'p';
	pl.p = ft_plane();
	ft_skipspace(&str);
	pl.p.mat.color = ft_get_color(&str);
	ft_skipspace(&str);
	pl.p.mat.reflective = ft_atof(&str);
	if (pl.p.mat.reflective < 0.0 || pl.p.mat.reflective > 1.0)
		return (ft_error("Plane reflection out of range."));
	ft_parse_plane_trans(&pl, org, dir);
	scene->world = ft_add_world(scene->world, pl);
	return (0);
}
