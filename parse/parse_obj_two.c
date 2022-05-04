/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:16:59 by migarcia          #+#    #+#             */
/*   Updated: 2022/05/04 19:56:54 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../algft/inc/algft.h"
#include "../libft/libft.h"
#include "parse.h"
#include "math.h"

void	ft_parse_cyl_trans(t_shape *cy, t_tuple org, t_tuple dir)
{
	cy->cy.transform = ft_mult_matrix(ft_transla_matrix(org.x, org.y, org.z),
			ft_scal_matrix(cy->cy.r / 2, cy->cy.r / 2, cy->cy.r / 2));
	cy->cy.transform = ft_mult_matrix(cy->cy.transform,
			ft_rotate_z_matrix(dir.x * M_PI / 2));
	cy->cy.transform = ft_mult_matrix(cy->cy.transform,
			ft_rotate_x_matrix(dir.z * M_PI / 2));
}

int	ft_parse_cylinder(t_scene *scene, char *str)
{
	t_shape	cy;
	t_tuple	dir;

	cy.cy = ft_cylinder();
	cy.c = 'c';
	str++;
	str++;
	ft_skipspace(&str);
	cy.cy.org = ft_parse_coor(&str);
	ft_skipspace(&str);
	dir = ft_parse_coor(&str);
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0
		|| dir.y > 1.0 || dir.z < -1.0 || dir.z > 1.0)
		return (ft_error("Cylinder 3D vector out of range."));
	dir = ft_norm_vec(dir);
	ft_skipspace(&str);
	cy.cy.r = ft_atof(&str);
	ft_skipspace(&str);
	cy.cy.max = ft_atof(&str) * 2;
	ft_skipspace(&str);
	cy.cy.mat.color = ft_get_color(&str);
	ft_parse_cyl_trans(&cy, cy.cy.org, dir);
	scene->world = ft_add_world(scene->world, cy);
	return (0);
}

void	ft_parse_co_trans(t_shape *cy, t_tuple org, t_tuple dir)
{
	cy->co.transform = ft_mult_matrix(ft_transla_matrix(org.x, org.y, org.z),
			ft_scal_matrix(cy->co.r, cy->co.r, cy->co.r));
	cy->co.transform = ft_mult_matrix(cy->co.transform,
			ft_rotate_z_matrix(dir.x * M_PI / 2));
	cy->co.transform = ft_mult_matrix(cy->co.transform,
			ft_rotate_x_matrix(dir.z * M_PI / 2));
}

int	ft_parse_cone(t_scene *scene, char *str)
{
	t_shape	cy;
	t_tuple	org;
	t_tuple	dir;
	float	n;

	cy.co = ft_cone();
	cy.c = 'o';
	str += 2;
	ft_skipspace(&str);
	org = ft_parse_coor(&str);
	ft_skipspace(&str);
	dir = ft_parse_coor(&str);
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0
		|| dir.y > 1.0 || dir.z < -1.0 || dir.z > 1.0)
		return (ft_error("Cylinder 3D vector out of range."));
	dir = ft_norm_vec(dir);
	ft_skipspace(&str);
	n = ft_atof(&str);
	ft_skipspace(&str);
	cy.co.max = 0;
	cy.co.min = n * -1;
	cy.co.mat.color = ft_get_color(&str);
	ft_parse_co_trans(&cy, org, dir);
	scene->world = ft_add_world(scene->world, cy);
	return (0);
}
