/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikgarci <mikgarci@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:26:33 by mikgarci          #+#    #+#             */
/*   Updated: 2022/04/06 20:17:58 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/algft.h"
#include <math.h>
#include <stdlib.h>

t_pattern	ft_stripe_pattern(t_color a, t_color b)
{
	t_pattern x;

	x.a = a;
	x.b = b;
	return (x);
}

t_color	ft_stripe_at(t_pattern x, t_tuple p)
{
	if (!fmodf(p.x, 2.0))
		return (x.a);
	return (x.b);
}
