/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:38:09 by mikgarci          #+#    #+#             */
/*   Updated: 2022/05/04 19:44:43 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"

t_camera	ft_cam(int hsize, int vsize, float fov)
{
	t_camera	a;

	a.hsize = hsize;
	a.vsize = vsize;
	a.fov = fov;
	a.trans = ft_iden_matrix(4, 4);
	return (a);
}
