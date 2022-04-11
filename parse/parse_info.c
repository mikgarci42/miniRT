/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:29:44 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/11 20:19:54 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../algft/inc/algft.h"
#include "./parse.h"
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
	return (0);
}

int	ft_parse_camera(t_scene *scene, char *str)
{
	str++;
	if (scene->nb_cam > 0)
		return (ft_error("Camera is already declared."));
	scene->nb_cam++;
	ft_skipspace(&str);
	scene->cam.point = ft_parse_coor(&str);
	ft_skipspace(&str);
	scene->cam.orient = ft_norm_vec(ft_parse_coor(&str));
	if (scene->cam.orient.x < -1.0 || scene->cam.orient.x > 1.0 || scene->cam.orient.y < -1.0 ||
		   	scene->cam.orient.y > 1.0 || scene->cam.orient.z < -1.0 || scene->cam.orient.x > 1.0)
		return (ft_error("Camera orientation out of range."));
	ft_skipspace(&str);
	scene->cam.fov = ft_atof(&str);
	if (scene->cam.fov < 0.0 || scene->cam.fov > 180.0)
		return (ft_error("Camera fov out of range."));
//	scene->cam = ft_camera(200, 100, scene->cam.fov);
	return (0);
}

int	ft_parse_light(t_scene *scene, char *str)
{
	t_light	*new;
	int		i;

	str++;
	new = malloc(sizeof(t_light) * scene->nb_light + 1);
	i = -1;
	while (++i < scene->nb_light)
		new[i] = scene->world.light[i];
	ft_skipspace(&str);
	new[i].pos = ft_parse_coor(&str);
	ft_skipspace(&str);
	new[i].bright = ft_atof(&str);
	if (new[i].bright < 0.0 || new[i].bright > 1.0)
		return (ft_error("Light shiny out of range."));
	new[i].i = ft_get_color(&str);
	if (new[i].i.r == -1)
		return (ft_error("Light color out of range."));
   	scene->world.light = new;
	free(new);
	ft_print_tup(scene->world.light->pos);
	return (0);
}
