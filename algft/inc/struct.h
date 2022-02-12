/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:40:26 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/12 03:26:34 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_matrix
{
	float	m[4][4];
	int		row;
	int		col;
}	t_matrix;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_generic {
	t_data	img;
	void	*mlx;
	void	*mlx_win;
}	t_generic;

typedef struct s_ray {
	t_tuple	org;
	t_tuple	dir;
}	t_ray;

typedef struct s_sphere {
	t_tuple		org;
	float		r;
	char		c;
	t_matrix	transform;
}	t_sphere;

typedef struct s_obj {
	float	t;
	t_sphere	obj;
}	t_inter;

typedef struct s_arr_inter {
	int		count;
	t_inter	*a;
}	t_arr_inter;

typedef struct s_light {
	t_tuple	pos;
	t_color	i;
}	t_light;

#endif
