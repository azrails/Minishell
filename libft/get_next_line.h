/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:42:17 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/13 13:42:19 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 15

typedef struct		s_lis
{
	char			*remainder;
	int				fd;
	struct s_lis	*next;
}					t_lis;

int					get_next_line(int fd, char **line);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str);
char				*ft_strchr(const char *str, int ch);
char				*ft_strjoin(char const *s1, char const *s2);
t_lis				*infonew(int fd, t_lis **info);

#endif
