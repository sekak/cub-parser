/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:53:17 by asekkak           #+#    #+#             */
/*   Updated: 2023/10/12 11:51:29 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "./libft/libft.h"

char	*get_cur_line(char *str);
char	*get_to_next(char *str);
char	*get_next_line(int fd);
// int		ft_strlen(char *str);
// char	*ft_strdup(char *str);
// char	*ft_strjoin(char *s1, char *s2);
char	*ft_copy(char *s1, char *s2, char *ptr);
// int		ft_strchr(char *str, int c);

#endif