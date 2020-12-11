/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:17:47 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 00:17:49 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int			cond(t_arg *arg, int i, int j, int eq)
{
	if ((i == 0 && arg->sarg[i] == '\\' && eq == 0) || (i != 0 &&
		(arg->sarg[i] == '\\' && arg->sarg[i - 1] != '\\') && eq == 0))
		j--;
	if ((arg->sarg[i] == '\'' || arg->sarg[i] == '\"') && eq == 0)
	{
		if (i != 0 && arg->sarg[i - 1] != '\\')
			j--;
	}
	if (arg->sarg[i] == '\'' && eq == 1)
	{
		if (i != 0 && arg->sarg[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	if (arg->sarg[i] == '\"' && eq == 2)
	{
		if (i != 0 && arg->sarg[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	return (j);
}

static	void		gts(t_tmp *tmp, t_config *cnf, char *ret)
{
	char	*ss;
	int		k;

	k = 0;
	ss = ft_itoa(cnf->excode);
	while (ss[k])
	{
		ret[tmp->j] = ss[k];
		tmp->j++;
		k++;
	}
	tmp->j--;
	tmp->i++;
	free(ss);
}

static	int			ccl(t_arg *arg, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (arg->sarg[tmp->i + 1] && arg->sarg[tmp->i + 1] == '?')
	{
		gts(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(arg->sarg, cnf->envl, tmp, ret);
		if (arg->sarg[tmp->i] == '\0')
			return (-1);
		tmp->i--;
	}
	return (tmp->i);
}

static	int			initi(t_tmp *tmp, t_arg *arg, t_env *env, t_config *cnf)
{
	int len;

	len = 0;
	tmp->i = 0;
	tmp->j = 0;
	tmp->eq = 0;
	len = specstrlen(arg->sarg, env, cnf);
	return (len);
}

char				*getstr(t_arg *arg, t_env *env, t_config *cnf)
{
	char	*ret;
	int		len;
	t_tmp	tmp;

	len = initi(&tmp, arg, env, cnf);
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (arg->sarg[tmp.i])
	{
		tmp.eq = checkq(arg->sarg, tmp.i, tmp.eq);
		if (((arg->sarg[tmp.i] != '$') || (tmp.i != 0 && arg->sarg[tmp.i] == '$'
			&& arg->sarg[tmp.i - 1] == '\\')) || tmp.eq == 1)
			ret[tmp.j] = arg->sarg[tmp.i];
		tmp.j = cond(arg, tmp.i, tmp.j, tmp.eq);
		if ((arg->sarg[tmp.i] == '$' && tmp.eq == 2)
			|| (arg->sarg[tmp.i] == '$' && tmp.eq == 0))
		{
			if ((tmp.i = ccl(arg, &tmp, ret, cnf)) == -1)
				break ;
		}
		tmp.j++;
		tmp.i++;
	}
	ret[tmp.j] = 0;
	return (ret);
}
