/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:37:26 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/11 20:19:55 by migarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../algft/inc/algft.h"
#include <stdio.h>

void	ft_skipspace(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

int	ft_comma(char **str)
{
	if (**str != ',')
		return(ft_error("Bad format.\n"));
	(*str)++;
	return (0);
}

t_color	ft_get_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = ft_mini_atoi(str);
	if (r < 0 || r > 255)
		r = -1;
	ft_comma(str);
	g = ft_mini_atoi(str);
	if (g < 0 || g > 255)
		r = -1;
	ft_comma(str);
	b = ft_mini_atoi(str);	
	if (b < 0 || b > 255)
		r = -1;
	return (ft_color(r, g, b));
}

t_tuple	ft_parse_coor(char **str)
{
	t_tuple	coor;

	coor.x = ft_atof(str);
	ft_comma(str);
	coor.y = ft_atof(str);
	ft_comma(str);
	coor.z = ft_atof(str);
	coor.w = 1;
	return (coor);
}
