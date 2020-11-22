/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:41:52 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/13 13:42:01 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char		*ft_strdup(const char *str)
{
	char	*s1;
	int		i;

	i = ft_strlen(str);
	if (!(s1 = malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != 0)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char		*ft_strchr(const char *str, int ch)
{
	char	*s1;
	int		i;

	s1 = (char *)str;
	i = 0;
	while (s1[i] != 0)
	{
		if (s1[i] == ch)
		{
			return (&s1[i]);
		}
		i++;
	}
	if (s1[i] == '\0' && ch == '\0')
		return (&s1[i]);
	return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	f;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen((char *)s1);
	f = ft_strlen((char *)s2);
	if (!(new = malloc(sizeof(*new) * (f + i + 1))))
		return (NULL);
	i = 0;
	f = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[f] != '\0')
	{
		new[i + f] = s2[f];
		f++;
	}
	new[i + f] = '\0';
	return (new);
}

t_lis		*infonew(int fd, t_lis **info)
{
	t_lis	*tmp;
	t_lis	*tmp2;

	tmp2 = *info;
	if (!(tmp = malloc(sizeof(t_lis))))
		return (NULL);
	tmp->fd = fd;
	tmp->remainder = NULL;
	tmp->next = NULL;
	if (!tmp2)
		*info = tmp;
	else
	{
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
	return (tmp);
}
