/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:14:34 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/29 18:12:30 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../algft/inc/algft.h"
#include "../libft/libft.h"
#include "parse.h"
#include <math.h>
#include <stdio.h>

int	ft_parse_ambient_light(t_scene *scene, char *str)
{
	str++;
	if (scene->amb.n > 0)
		return (ft_error("Ambient lighting is already declared."));
	scene->amb.n++;
	ft_skipspace(&str);
	scene->amb.r = ft_atof(&str);
	if (scene->amb.r < 0.0 || scene->amb.r > 1.0)
		return (ft_error("Ambient lighting ratio out of range."));
	ft_skipspace(&str);
	scene->amb.color = ft_get_color(&str);
	if (scene->amb.color.r == -1)
		return (ft_error("Ambient lighting color out of range."));
	scene->amb.color = ft_escal_color(scene->amb.color, scene->amb.r);
	ft_print_color(scene->amb.color);
	return (0);
}

int	ft_parse_camera(t_scene *scene, t_camera *c, char *str)
{
	float	fov;
	t_tuple	point;
	t_tuple	orient;

	str++;
	if (scene->nb_cam > 0)
		return (ft_error("Camera is already declared."));
	scene->nb_cam++;
	ft_skipspace(&str);
	point = ft_parse_coor(&str);
	ft_print_tup(point);
	ft_skipspace(&str);
	orient = ft_parse_coor(&str);
	if (orient.x < -1.0 || orient.x > 1.0 || orient.y < -1.0
		|| orient.y > 1.0 || orient.z < -1.0 || orient.z > 1.0)
		return (ft_error("Camera orientation out of range."));
	ft_skipspace(&str);
	fov = ft_atof(&str);
	if (fov < 0.0 || fov > 180.0)
		return (ft_error("Camera fov out of range."));
	fov = (fov / 180) * M_PI;
	*c = ft_camera(c->hsize, c->vsize, fov);
	orient = ft_add_tup(point, orient);
	c->trans = ft_view_trans(point, orient, ft_vector(0, 1, 0));
	return (0);
}

int	ft_parse_light(t_scene *scene, t_world *world, char *str)
{
	t_light	*new;
	int		i;

	new = malloc(sizeof(t_light) * (scene->nb_light + 1));
	i = -1;
	while (++i < scene->nb_light)
	{
		new[i].pos = world->light[i].pos;
		new[i].bright = world->light[i].bright;
		new[i].i = world->light[i].i;
	}
	str++;
	ft_skipspace(&str);
	new[i].pos = ft_parse_coor(&str);
	ft_skipspace(&str);
	new[i].bright = ft_atof(&str);
	if (new[i].bright < 0.0 || new[i].bright > 1.0)
		return (ft_error("Light brightness out of range."));
	ft_skipspace(&str);
	new[i].i = ft_get_color(&str);
	if (new[i].i.r == -1)
		return (ft_error("Light color out of range."));
	//free(world->light);
	world->light = new;
	scene->nb_light++;
	return (0);
}