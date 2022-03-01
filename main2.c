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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst =color;

}

void	ft_scale(int	x, int y, t_generic *g)
{
	int	a;
	int	b;

	a = x;
	b = y;
	my_mlx_pixel_put(&g->img, a, b, 255*255);
}

int		main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_ray	z;
	t_sphere	s;
	t_arr_inter		w;
	t_matrix	m;
	t_generic	g;


	s = ft_sphere(ft_point(0, 0, 0), 1.0);
	m = ft_iden_matrix(4, 4);
	ft_set_transform(&s, m);
	g.mlx = mlx_init();
	g.mlx_win = mlx_new_window(g.mlx, 100, 100, "prueba");
	g.img.img = mlx_new_image(g.mlx, 100, 100);
	g.img.addr = mlx_get_data_addr(g.img.img,
			&g.img.bits_per_pixel, &g.img.line_length, &g.img.endian);
	int y;
	int x;
	y = 0;
	while (y < 100)
	{
		float ym;
		ym = 3.5 - (0.07 * y);
		x = 0;
		while (x < 100)
		{
			float xm;
			xm = (-1.0 * 3.5) + (0.07 * x);
			z = ft_ray(ft_point(0, 0, -5), ft_norm_vec(ft_sub_tup(ft_point(xm, ym, 10), ft_vector(0, 0, -5))));
			w = ft_sphere_inter(z, s);
			if (w.count)
			{
				printf("x %d y %d \n", x, y);
				ft_scale(x, y, &g);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g.mlx, g.mlx_win, g.img.img, 0, 0);
	mlx_loop(g.mlx);
}

/*int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_generic	g;
	t_matrix	b;

	g.mlx = mlx_init();
	g.mlx_win = mlx_new_window(g.mlx, 500, 500, "prueba");
	g.img.img = mlx_new_image(g.mlx, 500, 500);
	g.img.addr = mlx_get_data_addr(g.img.img,
			&g.img.bits_per_pixel, &g.img.line_length, &g.img.endian);
	ft_scale(100, 0, &g);
	b = ft_rotate_z_matrix(M_PI_2 / 3);
	t_tuple	a;
	a = ft_point(100, 0, 0);
	a = ft_mult_matrix_tup(b, a);
	ft_scale(a.x, a.y, &g);
	while (a.x < 100)
	{
		a = ft_mult_matrix_tup(b, a);
		ft_scale(a.x, a.y, &g);
	}
	mlx_put_image_to_window(g.mlx, g.mlx_win, g.img.img, 0, 0);
	mlx_loop(g.mlx);
}*/

	//my_mlx_pixel_put(&gen->img, x, y, gen->value.color);
/*int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_matrix	z;
	t_matrix	a;
	float		r;
	t_tuple		c;
	
	z = ft_matrix(4, 4);
	a = ft_matrix(4, 4);
	z.m[0][0] = 1;
	z.m[0][1] = -2;
	z.m[0][2] = 2;
	z.m[0][3] = 2;
	z.m[1][0] = 0;
	z.m[1][1] = 4;
	z.m[1][2] = -2;
	z.m[1][3] = 1;
	z.m[2][0] = 1;
	z.m[2][1] = -2;
	z.m[2][2] = 4;
	z.m[2][3] = 0;
	z.m[3][0] = 1;
	z.m[3][1] = -1;
	z.m[3][2] = 2;
	z.m[3][3] = 2;
	a.m[0][0] = 1;
    a.m[0][1] = 7;
    a.m[0][2] = 14;
    a.m[0][3] = 0;
    a.m[1][0] = 9;
    a.m[1][1] = 4;
    a.m[1][2] = 18;
    a.m[1][3] = 18;
    a.m[2][0] = 2;
    a.m[2][1] = 4;
    a.m[2][2] = 5;
    a.m[2][3] = 5;
    a.m[3][0] = 1;
    a.m[3][1] = 7;
    a.m[3][2] = 1;
    a.m[3][3] = 11;


	//a = ft_trans_matrix(z);
	//r = ft_det_matrix(a);
	//a = ft_sub_matrix(a, 0, 0);
	//ft_print_matx(a);
	//r = ft_cofac_matrix(a, 1, 0);
	//printf("%lf\n", cos(3.14));
//	a = ft_scal_matrix(2, 3, 4);
//	ft_print_matx(a);
//	c = ft_point(0, 1, 0);
//	c = ft_mult_matrix_tup(a, c);
//	printf("%f %f %f\n", c.x, c.y, c.z);	
//	a = ft_rotate_z_matrix(M_PI / 2);
//	ft_print_matx(a);
//	c = ft_mult_matrix_tup(a, c);
//	printf("%f %f %f\n", c.x, c.y, c.z);	
	t_generic	g;
}*/



/*int	main(void)
{
	int	fd;
	t_tuple	pos;
	t_tuple	vel;
	t_tuple	grav;
	t_tuple	wind;

	pos = ft_point(0, 1, 0);
	vel = ft_mult_tup(ft_norm_vec(ft_vector(1, 1, 0)), 2.25);
	grav = ft_vector(0, -0.1, 0);
	wind = ft_vector(-0.01, 0, 0);
	fd = open("canvas.ppm", O_CREAT | O_TRUNC | O_RDWR, 0755);
	dup2(fd, 1);
	printf("P3\n40 40\n255\n");
	t_color **c;
	c = malloc(41 * sizeof(t_color *));
	int i;
	i = 0;
	while (i < 41)
	{
		c[i] = malloc(41 * sizeof(t_color));
		i++;
	}
	c[(int)pos.y][(int)pos.x].g = 255.0;
	while (pos.y > 0.0 && pos.x < 40)
	{
		pos = ft_add_tup(pos, vel);
		vel = ft_add_tup(ft_add_tup(grav, wind), vel);
		c[(int)pos.y][(int)pos.x].g = 255.0;
	}

	int	x;
	int y;
	
	y = 0; 
	while (y < 40)
	{
		x = 0;
		while (x < 40)
		{
			printf("%d %d %d ", (int) c[40 - y][x].r, (int) c[40 - y][x].g, (int) c[40 - x][y].b);
			x++;
		}
		printf("\n");
		y++;
	}
}*/