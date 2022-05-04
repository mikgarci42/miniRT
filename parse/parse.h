/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:58:00 by migarcia          #+#    #+#             */
/*   Updated: 2022/05/04 19:47:48 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//PARSE//
int		ft_check_file(t_scene *scene, t_camera *cam,
			t_world *world, char *file);

//PARSE_UTILS//
void	ft_skipspace(char **str);
int		ft_comma(char **str);
t_color	ft_get_color(char **str);
t_tuple	ft_parse_coor(char **str);

//PARSE_INFO//
int		ft_parse_ambient_light(t_scene *scene, char *str);
int		ft_parse_camera(t_scene *scene, t_camera *c, char *str);
int		ft_parse_light(t_scene *scene, t_world *world, char *str);

//PARSE_OBJ//
int		ft_parse_sphere(t_scene *scene, char *str);
int		ft_parse_plane(t_scene *scene, char *str);
int		ft_parse_cylinder(t_scene *scene, char *str);
int		ft_parse_cone(t_scene *scene, char *str);

//PARSE_OBJ_TWO//
int		ft_parse_cylinder(t_scene *scene, char *str);

#endif 
