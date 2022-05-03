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

/*void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst =color;

}*/
/*
void	ft_scale(int	x, int y, t_generic *g, t_color c)
{
	int	a;
	int	b;
	int value;

	value = 0;
	if (c.r > 1)
		value = value + 255 * 256 * 256;
	else if (c.r > 0)
		value = value + ((int)(c.r * 255)) * 256 * 256;
	if (c.g > 1)
		value = value + 255 * 256;
	else if (c.g > 0)
		value = value + ((int)(c.g * 255)) * 256;
	if (c.b > 1)
		value = value + 255;
	else if (c.b > 0)
		value = value + ((int)(c.b * 255));

	a = x;
	b = y;*/
/*	if (col.r > 1.0)
		col.r = 1.0;
	if (col.g > 1.0)
		col.g = 1.0;
	if (col.b > 1.0)
		col.b = 1.0;
	if (col.r < 0.0)
		col.r = 0.0;
	if (col.g < 0.0)
		col.g = 0.0;
	if (col.b < 0.0)
		col.b = 0.0;*/
	//my_mlx_pixel_put(&g->img, a, b
/*	my_mlx_pixel_put(&g->img, a, b, value);
}*/
/*
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_tuple	eyev;
	t_tuple	normalv;
	t_light	light;
	t_color color;
	t_material m;
	t_tuple	pos;

	m = ft_materials();
	pos = ft_point(0, 0, 0);
	eyev = ft_vector(0, sqrtf(2)/2, sqrtf(2)/2);
	normalv = ft_vector(0, 0, -1);
	light = ft_point_light(ft_point(0, 0, -10), ft_color(1, 1, 1));
	color = ft_lighting(m, light, pos, eyev, normalv);
	printf("%f %f %f\n", color.r, color.g, color.b);
}
*/

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


/*int main(void)
{
	t_material	m;

	m = ft_materials();
	m.ispattern = true;
	m.pattern = ft_stripe_pattern(ft_color(0, 0, 0), ft_color(1, 1, 1));
	m.ambient = 1;
	m.diffuse = 0;
	m.specular = 0;
	t_tuple  eyev;
	eyev = ft_vector(0, 0, -1);
	t_tuple  normalv;
	normalv = ft_vector(0, 0, -1);
	t_light l;
	l = ft_point_light(ft_point(0, 0, -10), ft_color(1, 1, 1));
	t_color w;

	w = ft_lighting(m, l, ft_point(1.1, 0, 0), eyev, normalv, false);
	ft_print_color(w);
}*/


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
//        scene->cam = ft_camera(W_WIN, H_WIN, M_PI / 3);
//	scene->cam.trans = ft_view_trans(ft_point(1, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	scene->nb_light	= 0;
	scene->cam = ft_cam(W_WIN, H_WIN, M_PI/2);
	//c->trans = ft_view_trans(ft_point(1, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));
	//scene->world.light = malloc(sizeof(t_light));
	//scene->world.light[0].bright = 0.0;
//	scene->world.light = ft_point_light(ft_point(-10, 10, -10), ft_color(0, 0, 0));
	scene->world.count = 0;
}

void	ft_init_mlx(t_scene *scene)
{
	
	scene->g.mlx = mlx_init();
	scene->g.mlx_win = mlx_new_window(scene->g.mlx, W_WIN, H_WIN, "prueba");
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
