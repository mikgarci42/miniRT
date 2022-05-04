/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarcia <migarcia@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:00:41 by migarcia          #+#    #+#             */
/*   Updated: 2022/05/04 19:48:44 by mikgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *s)
{
	int		i;
	int		size;
	char	*str;

	if (!s)
		return (NULL);
	size = ft_strlen1(s, '\n') + 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_cut_content(char *s, char *buff)
{
	int		i;
	char	*str;
	int		init;
	int		size;

	i = 0;
	if (!ft_strchr1(s, '\n'))
	{
		ft_free(s);
		return (NULL);
	}
	size = ft_strlen1(s, '\0') - ft_strlen1(buff, '\0');
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	init = ft_strlen1(s, '\n') + 1;
	while (i < size && s[init + i])
	{
		str[i] = s[init + i];
		i++;
	}
	str[i] = '\0';
	ft_free(s);
	return (str);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(ft_strlen1(s1, '\0') + ft_strlen1(s2, '\0') + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[j + i] = '\0';
	ft_free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff;
	ssize_t		size;

	if (fd == 2 || fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (100 + 1));
	size = 1;
	while (size > 0 && !ft_strchr1(str, '\n'))
	{
		size = read(fd, buff, 100);
		if (size < 0)
			break ;
		buff[size] = '\0';
		str = ft_strjoin1(str, buff);
	}
	ft_free(buff);
	if (size < 0)
		return (NULL);
	buff = ft_get_line(str);
	str = ft_cut_content(str, buff);
	if (!size && !ft_strlen1(buff, 0))
		return (ft_free(buff));
	return (buff);
}
