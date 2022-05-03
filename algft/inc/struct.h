/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:40:26 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/29 18:29:07 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
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

	typedef struct s_pattern
	{
		t_color	a;
		t_color	b;
	}	t_pattern;

	typedef struct s_material
	{
		bool		ispattern;
		t_pattern	pattern;
		float	ambient;
		float	diffuse;
		float	specular;
		float	shininess;
		float	reflective;
		t_color	color;
	}	t_material;

	typedef struct s_ray {
		t_tuple	org;
		t_tuple	dir;
	}	t_ray; 

	typedef struct s_sphere {
		t_tuple		org;
		float		r;
		t_matrix	transform;
		t_material	mat;
	}	t_sphere;

	typedef struct s_plane {
		t_matrix	transform;
	t_material	mat;
	t_tuple		org;
	t_tuple		norm;
}	t_plane;

typedef struct s_cylinder {
	t_tuple		org;
	float		r;
	t_material	mat;
	t_matrix	transform;
	float		min;
	float		max;
	bool		closed;
}	t_cylinder;

typedef struct s_cone {
	t_tuple		org;
	t_tuple		dir;
	float		r;
	t_material	mat;
	t_matrix	transform;
	float		min;
	float		max;
	bool		closed;
}	t_cone;

typedef struct s_cube {
	t_material	mat;
	t_tuple		org;
	t_matrix	transform;
}	t_cube;

typedef struct s_shape {
	t_sphere	s;
	t_plane		p;
	t_cylinder	cy;
	t_cube		cu;
	t_cone		co;
	char		c;
}	t_shape;

typedef struct s_inter {
	float	t;
	t_shape	obj;
}	t_inter;

typedef struct s_arr_inter {
	int			count;
	t_inter		*a;
}	t_arr_inter;

typedef struct s_light {
	t_tuple	pos;
	t_color	i;
	float	bright;
}	t_light;

typedef struct s_world {
	t_light		*light;
	int			count;
	t_shape		*s;
}	t_world;

typedef struct s_comps {
	float		t;
	t_shape		obj;
	t_tuple		p;
	t_tuple		eye;
	t_tuple		norm;
	bool		inside;
	t_tuple		op;
	t_tuple		reflectv;
}	t_comps;

typedef struct s_camera {
	double		hsize;
	double		vsize;
	double		hw;
	double		hh;
	double		ps;
	double		fov;
	t_matrix	trans;	
}	t_camera;

typedef	struct s_ambient {
	int		n;
	float	r;
	t_color	color;
} t_ambient;

typedef	struct s_scene {
	t_ambient	amb;
	int			nb_cam;
	t_camera	cam;
	t_generic	g;
	int			nb_light;
	int			lid;
	t_world		world;
} t_scene;

#endif
