/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:51:57 by asekkak           #+#    #+#             */
/*   Updated: 2022/11/01 13:01:04 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*cur_line;
	int			read_vl;
	static char	*next;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_vl = 1;
	while (read_vl != 0 && !(ft_strchr(next, '\n')))
	{
		read_vl = read(fd, buff, BUFFER_SIZE);
		if (read_vl < 0)
			return (0);
		buff[read_vl] = '\0';
		next = ft_strjoin(next, buff);
	}
	cur_line = get_cur_line(next);
	next = get_to_next(next);
	return (cur_line);
}

char	*get_to_next(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	if (ft_strlen(str + i) == 0)
		return (free(str), NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!ptr)
		return (0);
	while (str[i])
		ptr[j++] = str[i++];
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

char	*get_cur_line(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
		if (ptr[i - 1] == '\n')
			break ;
	}
	ptr[i] = '\0';
	return (ptr);
}
