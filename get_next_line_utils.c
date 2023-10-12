/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:49:44 by asekkak           #+#    #+#             */
/*   Updated: 2023/10/12 11:51:13 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_copy(char const *s1, char *s2, char const  *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		ptr[j + i] = s2[j];
		j++;
	}
	ptr[j + i] = '\0';
	free (s1);
	return (ptr);
}

char	*ft_strjoin(char const  *s1, char const  *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	return (ft_copy(s1, s2, ptr));
}

int	ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == 0)
		return ((char)&str[i]);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char)&str[i]);
		i++;
	}
	return (0);
}
