/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:26:33 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/20 18:43:53 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_pattern	ft_stripe_pattern(t_color a, t_color b)
{
	t_pattern x;

	x.a = a;
	x.b = b;
	return (x);
}

t_color	ft_stripe_at(t_pattern x, t_tuple p)
{
	if (fmod((sqrtf(powf(p.x, 2) + powf(p.y, 2)) + fabs(p.z)), 2.0) > 1)
		return (x.a);
	return (x.b);
}
