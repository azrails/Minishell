/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:21:57 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/28 20:22:00 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		countenv(t_env *env, char *s, int i)
{
	int		j;
	int		c;
	char	*tmp;
	t_env	*e;

	c = 0;
	e = env;
	j = i;
	while (s[j])
	{
		if (s[j] == ' ')
			break;
		j++;
	}
	tmp = malloc(sizeof(char) * (j - i) + 1);
	while (i < j)
	{
		tmp[c] = s[i];
		i++;
		c++;
	}
	tmp[c] = 0;
	while (e)
	{
		if (!(ft_strcmp(tmp, e->key)))
			break;
		e = e->next;
	}
	c = ft_strlen(e->value);
	return (c);
}

static	int		specstrlen(char *s, t_env *env)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != '$') || (i != 0 && s[i] == '$' && s[i - 1] == '\\'))
			count++;
		else if (s[i] == '$')
		{
			count += countenv(env, s, ++i);
			while (s[i] && s[i] != ' ')
				i++;
			i--;
		}
		i++;
	}
	return (count);
}

static	int		ptenv(char *str, t_env *env, int i, char *s, int k)
{
	t_env	*e;
	int		j;
	char	*tmp;
	int		c;

	c = 0;
	j = i;
	e = env;
	while (str[j])
	{
		if (str[j] == ' ')
			break;
		j++;
	}
	tmp = malloc(sizeof(char) * (j - i));
	while (i < j)
	{
		tmp[c] = str[i];
		i++;
		c++;
	}
	tmp[c] = 0;
	while (e)
	{
		if (!(ft_strcmp(tmp, e->key)))
			break;
		e = e->next;
	}
	j = 0;
	while (e->value[j])
	{
		s[k] = e->value[j];
		k++;
		j++;
	}
	return (k - 1);
}

char	*getstr(t_arg *arg, t_env *env)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (arg->quote == 1)
		len = ft_strlen(arg->sarg);
	else if (arg->quote == 2 || arg->quote == 0)
		len = specstrlen(arg->sarg, env);
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (arg->sarg[i])
	{
		if (((arg->sarg[i] != '$') || (i != 0 && arg->sarg[i] == '$' && arg->sarg[i - 1] == '\\')) || arg->quote == 1)
			ret[j] = arg->sarg[i];
		else if ((arg->sarg[i] == '$' && arg->quote == 2) || (arg->sarg[i] == '$' && arg->quote == 0))
		{
			j = ptenv(arg->sarg, env, ++i, ret, j);
			while (arg->sarg[i] && arg->sarg[i] != ' ')
				i++;
			i--;
		}
		j++;
		i++;
	}
	ret[j] = 0;
	return (ret);
}