/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:33:09 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 19:44:45 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "algft/inc/algft.h"
#include "parse/parse.h"
#include <fcntl.h>

void	ft_init_scene(t_scene *scene)
{
	scene->amb.n = 0;
	scene->amb.r = 0.0;
	scene->amb.color = ft_color(0, 0, 0);
	scene->nb_cam = 0;
	scene->nb_light = 0;
	scene->cam = ft_cam(200, 100, M_PI / 2);
	scene->world.count = 0;
}

void	ft_init_mlx(t_scene *scene)
{
	scene->g.mlx = mlx_init();
	scene->g.mlx_win = mlx_new_window(scene->g.mlx, W_WIN, H_WIN, "prueba");
	scene->g.img.img = mlx_new_image(scene->g.mlx, W_WIN, H_WIN);
	scene->g.img.addr = mlx_get_data_addr(scene->g.img.img,
			&scene->g.img.bits_per_pixel, &scene->g.img.line_length,
			&scene->g.img.endian);
}

int	close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

void	ft_mlx_loop(t_scene *scene)
{
	mlx_put_image_to_window(scene->g.mlx,
		scene->g.mlx_win, scene->g.img.img, 0, 0);
	mlx_hook(scene->g.mlx_win, 17, 1L << 17, close_program, 0);
	mlx_loop(scene->g.mlx);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		printf("Usage: ./miniRT <filename.rt>\n");
		return (1);
	}
	ft_init_scene(&scene);
	if (ft_check_file(&scene, &scene.cam, &scene.world, argv[1]))
		return (1);
	ft_init_mlx(&scene);
	ft_render(scene);
	ft_mlx_loop(&scene);
}
