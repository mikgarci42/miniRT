/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:50:31 by migarcia          #+#    #+#             */
/*   Updated: 2022/05/08 13:17:43 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../algft/inc/algft.h"
#include "../libft/libft.h"
#include "parse.h"
#include "stdio.h"

void	ft_skipspace(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

int	ft_comma(char **str)
{
	if (**str != ',')
		ft_exit("Bad format.", 1);
	(*str)++;
	return (0);
}

t_color	ft_get_color(char **str)
{
	float	r;
	float	g;
	float	b;

	ft_skipspace(str);
	if (**str == ',')
		ft_exit("Bad format", 1);
	r = ft_mini_atoi(str);
	if (r < 0 || r > 255)
		ft_exit("Color out of range", 1);
	else
		r = r / 255;
	ft_comma(str);
	g = ft_mini_atoi(str);
	if (g < 0 || g > 255)
		ft_exit("Color out of range", 1);
	else
		g /= 255;
	ft_comma(str);
	b = ft_mini_atoi(str);
	if (b < 0 || b > 255)
		ft_exit("Color out of range", 1);
	else
		b /= 255;
	return (ft_color(r, g, b));
}

t_tuple	ft_parse_coor(char **str)
{
	t_tuple	coor;

	if ((**str < 48 && (**str != 43 && **str != 45)) || **str > 57)
		ft_exit("Bad format.", 1);
	coor.x = ft_atof(str);
	ft_comma(str);
	if ((**str < 48 && (**str != 43 && **str != 45)) || **str > 57)
		ft_exit("Bad format.", 1);
	coor.y = ft_atof(str);
	ft_comma(str);
	if ((**str < 48 && (**str != 43 && **str != 45)) || **str > 57)
		ft_exit("Bad format.", 1);
	coor.z = ft_atof(str);
	coor.w = 1;
	return (coor);
}
