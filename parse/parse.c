/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:12:04 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/29 17:44:38 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../algft/inc/algft.h"
#include "./parse.h"
#include <fcntl.h>

int	ft_parsing_type(t_scene *scene, t_camera *c, t_world *world, char *str)
{
	(void) str;
	int	check;

	check = 0;
	if (str[0] == 'A' && ft_is_spacetab(str[1]))
		check = ft_parse_ambient_light(scene, str);
	else if (str[0] == 'C' && ft_is_spacetab(str[1]))
		check = ft_parse_camera(scene, c, str);
	else if (str[0] == 'L' && ft_is_spacetab(str[1]))
		check = ft_parse_light(scene, world, str);
	else if (str[0] == 's' && str[1] == 'p' && ft_is_spacetab(str[2]))
		check = ft_parse_sphere(scene, str);
	else if (str[0] == 'p' && str[1] == 'l' && ft_is_spacetab(str[2]))
		check = ft_parse_plane(scene, str);
	else if (str[0] == 'c' && str[1] == 'y' && ft_is_spacetab(str[2]))
		check = ft_parse_cylinder(scene, str);
	else if (str[0] == 'c' && str[1] == 'o' && ft_is_spacetab(str[2]))
		check = ft_parse_cone(scene, str);
	else if (str[0] == '\n' || str[0] == '\0')
		return (0);
	else
		return(ft_error("character invalid."));
	return (check);
}

int	ft_parse(t_scene *scene, t_camera *c, t_world *world, char *file)
{
	int		fd;
	char	*line;
	int		check;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_error("Invalid file."));
	line = get_next_line(fd);
	check = 0;
	while (check == 0 && line)
	{
		check = ft_parsing_type(scene, c, world, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		free(line);
	close (fd);
	if (scene->nb_cam == 0)
		return(ft_error("No Camera."));
	if (scene->nb_light == 0)
		return(ft_error("No Lights."));
	return (check);
}

int	ft_check_file(t_scene *scene, t_camera *cam, t_world *world, char *file)
{
	int		fd;
	int		len;
	char	*ext;
	int		e_len;
	
	fd = 0;
	e_len = 2;
	ext = ".rt";
	len = ft_strlen(file) - 1;
	while (e_len >= 0)
	{
		if (len < 1 || ext[e_len] != file[len])
                	ft_exit("Invalid extension file.", 1);
		e_len--;
		len--;
	}
	return (ft_parse(scene, cam, world, file));
}
