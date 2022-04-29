/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/10/08 17:41:11 by migarcia          #+#    #+#             */
/*   Updated: 2022/04/26 18:38:30 by migarcia         ###   ########.fr       */
=======
/*   Created: 2021/07/20 18:54:16 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:28:36 by iibanez-         ###   ########.fr       */
>>>>>>> a717cfe09883eaafc060b58fec5221d9245b3131
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

char	*ft_strchr1(char	*s, char c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_strlen1(char	*s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}
