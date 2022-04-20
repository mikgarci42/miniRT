#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "algft/inc/algft.h"
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





int	main(int argc, char **argv)
{	
	(void) argc;
	(void) argv;
	t_world		w;
	t_camera	c;
	t_generic	g;

	t_shape	p;
//	t_shape cy;



	p.c = 'p';
	p.p = ft_plane();
//	p.p.transform = ft_rotate_z_matrix(M_PI_4);
	p.p.mat = ft_materials();
	p.p.mat.color = ft_color(0, 0.9, 0.9);
	p.p.mat.specular = 0;
	p.p.mat.ispattern = true;
	p.p.mat.pattern = ft_stripe_pattern(ft_color(0, 0, 0), ft_color(1, 1, 1));

//	cy.s = ft_sphere();
//	cy.c = 's';
//	cy.s.mat = ft_materials();
//	cy.s.mat.specular = 0;
//	cy.s.mat.color = ft_color(0.1, 1, 0.5);

	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	w.count = 0;

	w = ft_add_world(w, p);
//	w = ft_add_world(w, cy);

	c = ft_camera(200, 100, M_PI / 3);
	c.trans = ft_view_trans(ft_point(1, 1.5, -5), ft_point(0, 1, 0), ft_vector(0, 1, 0));

	g.mlx = mlx_init();
	g.mlx_win = mlx_new_window(g.mlx, 200, 100, "prueba");
	g.img.img = mlx_new_image(g.mlx, 200, 100);
	g.img.addr = mlx_get_data_addr(g.img.img,
			&g.img.bits_per_pixel, &g.img.line_length, &g.img.endian);


	ft_render(c, w, g);


	mlx_put_image_to_window(g.mlx, g.mlx_win, g.img.img, 0, 0);
	mlx_loop(g.mlx);
}
