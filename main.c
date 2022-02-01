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
void ft_print_tup(t_tuple tuple)
{
	if (tuple.w)
		printf("point ");
	else
		printf("vector ");
	printf("(%f %f %f)\n", tuple.x, tuple.y, tuple.z);
}

void	ft_print_matx(t_matrix a)
{
	int	row;
	int	col;

	col = 0;
	while (col < a.col)
	{
		row = 0;
		while (row < a.row)
		{
			printf("%f ", a.m[col][row]);
			row++;
		}
		printf("\n");
		col++;
	}
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_matrix	z;
	t_matrix	a;
	float		r;
	
	z = ft_matrix(4, 4);
	z.m[0][0] = -2;
	z.m[0][1] = -8;
	z.m[0][2] = 3;
	z.m[0][3] = 5;
	z.m[1][0] = -3;
	z.m[1][1] = 1;
	z.m[1][2] = 7;
	z.m[1][3] = 3;
	z.m[2][0] = 1;
	z.m[2][1] = 2;
	z.m[2][2] = -9;
	z.m[2][3] = 6;
	z.m[3][0] = -6;
	z.m[3][1] = 7;
	z.m[3][2] = 7;
	z.m[3][3] = -9;
	//a = ft_trans_matrix(z);
	ft_print_matx(z);
	r = ft_det_matrix(z);
	//a = ft_sub_matrix(a, 0, 0);
	//ft_print_matx(a);
	//r = ft_cofac_matrix(a, 1, 0);
	printf("%f\n", r);
	//a = ft_sub_matrix(a, 0, 0);
	//ft_print_matx(a);
}



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
