/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:35:51 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/02 20:39:10 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGFT_H
# define ALGFT_H

#define EPSILON 0.00001

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

//CREATE TUPLE// POINT 1 VECTOR 0
t_tuple	ft_point(float x, float y, float z);
t_tuple	ft_vector(float x, float y, float z);

//OPERATION TUPLE//
t_tuple	ft_add_tup(t_tuple a, t_tuple b);
t_tuple	ft_sub_tup(t_tuple a, t_tuple b);
t_tuple ft_div_tup(t_tuple a, float d);
t_tuple ft_mult_tup(t_tuple a, float m);
t_tuple ft_neg_tup(t_tuple a);
//TWO//
float	ft_mag_vec(t_tuple v);
t_tuple ft_norm_vec(t_tuple v);
float	ft_dot_prod(t_tuple a, t_tuple b);
t_tuple	ft_cross_prod(t_tuple a, t_tuple b);

//COLORS//
t_color	ft_init_color(float	r, float g, float b);
t_color	ft_add_color(t_color a, t_color b);
t_color	ft_sub_color(t_color a, t_color b);
t_color	ft_escal_color(t_color a, float b);
t_color	ft_mult_color(t_color a, t_color b);

//MATRIX//
t_matrix	ft_matrix(int row, int column);
t_matrix	ft_mult_matrix(t_matrix a, t_matrix b);
t_tuple		ft_mult_matrix_tup(t_matrix a, t_tuple b);
t_matrix	ft_trans_matrix(t_matrix a);
t_matrix	ft_escal_matrix(t_matrix a, float w);
//Determinant//
t_matrix	ft_sub_matrix(t_matrix a, int row, int col);
float		ft_minor_matrix(t_matrix a, int row, int col);
float		ft_det_matrix(t_matrix a);
float		ft_cofac_matrix(t_matrix a, int row, int col);
//Inverse//
t_matrix	ft_atta_matrix(t_matrix	a);
t_matrix	ft_inver_matrix(t_matrix a);
t_matrix	ft_iden_matrix(int row, int col);
//Transformations//
t_matrix	ft_transla_matrix(float x, float y, float z);
t_matrix	ft_scal_matrix(float x, float y, float z);
t_matrix	ft_rotate_x_matrix(float x);
t_matrix	ft_rotate_y_matrix(float x);
t_matrix	ft_rotate_z_matrix(float x);
t_matrix	ft_shear_matrix(t_tuple b, t_tuple c);

//ERROR//
void	ft_error(char *str, int	i);
#endif
