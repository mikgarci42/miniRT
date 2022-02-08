/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:24:21 by mikgarci          #+#    #+#             */
/*   Updated: 2022/02/08 20:25:27 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"

t_sphere	ft_sphere(t_tuple org, float r)
{
	t_sphere	a;

	a.c = 's';
	a.r = r;
	a.org = ft_point(org.x, org.y, org.z);
	return (a);
}	
