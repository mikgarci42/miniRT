#include "../algft/inc/algft.h"
#include "../libft/libft.h"
#include "parse.h"
#include <stdio.h>
#include <math.h>

int     ft_parse_sphere(t_scene *scene, char *str)
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
	sp.s.transform = ft_mult_matrix(ft_transla_matrix(org.x, org.y, org.z), ft_scal_matrix(di/2, di/2, di/2));
	ft_skipspace(&str);
	sp.s.mat.color = ft_get_color(&str);
	if (sp.s.mat.color.r == -1)
		return (ft_error("Sphere color out of range."));
	scene->world = ft_add_world(scene->world, sp);
	return (0);
}

int     ft_parse_plane(t_scene *scene, char *str)
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
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0 ||
			dir.y > 1.0 || dir.z < -1.0 || dir.z > 1.0)
		return (ft_error("Plane 3D vector out of range."));
	dir = ft_norm_vec(dir);
	pl.c = 'p';
	pl.p = ft_plane();
	ft_skipspace(&str);
	pl.p.mat.color = ft_get_color(&str);
	if (pl.p.mat.color.r == -1)
		return (ft_error("Plane color out of range."));
	pl.p.transform = ft_mult_matrix(pl.p.transform, ft_transla_matrix(org.x, org.y, org.z)); 
	pl.p.transform = ft_mult_matrix(pl.p.transform, ft_rotate_z_matrix(dir.x * M_PI / 2)); 
	pl.p.transform = ft_mult_matrix(pl.p.transform, ft_rotate_x_matrix(dir.z * M_PI / 2)); 
	scene->world = ft_add_world(scene->world, pl);
	return (0);
}

int	ft_parse_cylinder(t_scene *scene, char *str)
{
	t_shape	cy;
	t_tuple	org;
	t_tuple	dir;
	
	cy.cy = ft_cylinder();
	cy.c = 'c';
	str++;
	str++;
	ft_skipspace(&str);
	org = ft_parse_coor(&str);
	ft_skipspace(&str);
	dir = ft_parse_coor(&str);
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0 ||
			dir.y > 1.0 || dir.z < -1.0 || dir.z > 1.0)
		return (ft_error("Cylinder 3D vector out of range."));
	dir = ft_norm_vec(dir);
	ft_skipspace(&str);
	cy.cy.r = ft_atof(&str);
	ft_skipspace(&str);
	cy.cy.max = ft_atof(&str);
	ft_skipspace(&str);
	cy.cy.mat.color = ft_get_color(&str);
	if (cy.cy.mat.color.r == -1)
		return (ft_error("Cylinder color out of range."));
	cy.cy.transform = ft_mult_matrix(ft_transla_matrix(org.x, org.y, org.z), ft_scal_matrix(cy.cy.r/2, cy.cy.r/2, cy.cy.r/2));
	cy.cy.transform = ft_mult_matrix(cy.cy.transform, ft_rotate_z_matrix(dir.x * M_PI / 2)); 
	cy.cy.transform = ft_mult_matrix(cy.cy.transform, ft_rotate_x_matrix(dir.z * M_PI / 2)); 
	scene->world = ft_add_world(scene->world, cy);
	return (0);
}
