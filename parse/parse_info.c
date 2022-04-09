/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:29:44 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/09 13:04:03 by migarcia         ###   ########.fr       */
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
	t_camera	*next;
	t_camera	*begin;

	begin = scene->cam;
	str++;
	scene->nb_cam++;
	next = malloc(sizeof(t_camera));
	next->next = NULL;
	while (scene->cam)
		scene->cam = scene->cam->next;
	ft_skipspace(&str);
	next->point = ft_parse_coor(&str);
	ft_skipspace(&str);
	next->orient = ft_norm_vec(ft_parse_coor(&str));
	if (next->orient.x < -1.0 || next->orient.x > 1.0 || next->orient.y < -1.0 ||
		   	next->orient.y > 1.0 || next->orient.z < -1.0 || next->orient.x > 1.0)
		return (ft_error("Camera orientation out of range."));
	ft_skipspace(&str);
	next->fov = ft_atof(&str);
	if (next->fov < 0.0 || next->fov > 180.0)
		return (ft_error("Camera fov out of range."));
	*next = ft_camera(200, 100, next->fov);
	if (begin)
		scene->cam = begin;
	scene->cam = next;
	ft_print_tup(next->orient);
	return (0);
}
