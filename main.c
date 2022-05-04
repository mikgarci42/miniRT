#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "algft/inc/algft.h"
#include "parse/parse.h"
#include <fcntl.h>

bool	ft_equal(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return (true);
	return (false);
}

void	ft_read_pixel(FILE *f, float red, float green, float blue)
{
	if (red < 0)
		fprintf(f, "0 ");
	else if (red > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ",(int) (red * 255));
	if (green < 0)
		fprintf(f, "0 ");
	else if (green > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ", (int) (green * 255));
	if (blue < 0)
		fprintf(f, "0");
	else if (blue > 1)
		fprintf(f, "255");
	else
		fprintf(f, "%i", (int) (blue * 255));
}

t_camera	ft_cam(int hsize, int vsize, float fov)
{
	t_camera	a;

	a.hsize = hsize;
	a.vsize = vsize;
	a.fov = fov;
	a.trans = ft_iden_matrix(4, 4);
	return (a);
}

void	ft_init_scene(t_scene *scene)
{
	scene->amb.n = 0;
	scene->amb.r = 0.0;
	scene->amb.color = ft_color(0, 0, 0);
	scene->nb_cam = 0;
	scene->nb_light	= 0;
	scene->cam = ft_cam(W_WIN, H_WIN, M_PI/2);
	scene->world.count = 0;
}

void	ft_init_mlx(t_scene *scene)
{
	
	scene->g.mlx = mlx_init();
	scene->g.mlx_win = mlx_new_window(scene->g.mlx, W_WIN, H_WIN, "MINIRT");
	scene->g.img.img = mlx_new_image(scene->g.mlx, W_WIN, H_WIN);
	scene->g.img.addr = mlx_get_data_addr(scene->g.img.img,
		&scene->g.img.bits_per_pixel, &scene->g.img.line_length, &scene->g.img.endian);
}

int	close_program(void *param)
{
        param = (void *)param;
        exit(EXIT_SUCCESS);
        return (1);
}

void	ft_mlx_loop(t_scene *scene)
{
	mlx_put_image_to_window(scene->g.mlx, scene->g.mlx_win, scene->g.img.img, 0, 0);
	mlx_hook(scene->g.mlx_win, 17, 1L<<17, close_program, 0);
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
