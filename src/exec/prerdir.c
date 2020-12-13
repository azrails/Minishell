/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prerdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:17:49 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/08 12:17:51 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void		gtc(t_tmp *tmp, t_config *cnf, char *ret)
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

static	int			ccg(char *str, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (str[tmp->i + 1] && str[tmp->i + 1] == '?')
	{
		gtc(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(str, cnf->envl, tmp, ret);
		if (str[tmp->i] == '\0')
			return (-1);
		tmp->i--;
	}
	return (tmp->i);
}

static	int			condi(char *str, int i, int j, int eq)
{
	if ((i == 0 && str[i] == '\\' && eq == 0) || (i != 0 &&
		(str[i] == '\\' && str[i - 1] != '\\') && eq == 0))
		j--;
	if ((str[i] == '\'' || str[i] == '\"') && eq == 0)
	{
		if (i != 0 && str[i - 1] != '\\')
			j--;
	}
	if (str[i] == '\'' && eq == 1)
	{
		if (i != 0 && str[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	if (str[i] == '\"' && eq == 2)
	{
		if (i != 0 && str[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	return (j);
}





static	int			inn(char *str, t_env *env, t_config *cnf, t_tmp *tmp)
{
	int len;

	len = 0;
	tmp->i = 0;
	tmp->j = 0;
	tmp->eq = 0;
	tmp->st = 0;
	len = specstrlen(str, cnf);
	return (len);
}

static	void		gtcc(t_tmp *tmp, t_config *cnf, char *ret)
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

static	int			condis(char *str, t_tmp *tmp,  int eq)
{
	if ((str[tmp->i] == '\'' || str[tmp->i] == '\"') && eq == 0 && tmp->st == 0)
		tmp->j--;
	if (str[tmp->i] == '\'' && eq == 1)
		tmp->j--;
	if (str[tmp->i] == '\"' && eq == 2 && tmp->st == 0)
		tmp->j--;
	return (tmp->j);
}

static	int			ccgg(char *str, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (str[tmp->i + 1] && str[tmp->i + 1] == '?')
	{
		gtcc(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(str, cnf->envl, tmp, ret);
		tmp->j--;
		if (str[tmp->i] == '\0')
			return (tmp->i - 1);
		tmp->i--;
	}
	return (tmp->i);
}

char				*gettruepth(char *str, t_env *env, t_config *cnf)
{
	char	*ret;
	int		len;
	t_tmp	tmp;

	len = inn(str, env, cnf, &tmp);
	ret = malloc(sizeof(char) * len + 1);
	while (str[tmp.i])
	{
		tmp.eq = checkqq(str, tmp.i, tmp.eq, &tmp);
		//printf("eq %d %d %d\n",tmp.eq, tmp.st, tmp.i);
		if ((str[tmp.i] != '$') || (str[tmp.i] == '$' &&
			tmp.st == 1) || tmp.eq == 1)
			ret[tmp.j] = str[tmp.i];
		if ((str[tmp.i] == '$' && tmp.eq != 1 && tmp.st == 0))
			tmp.i = ccgg(str, &tmp, ret, cnf);
		tmp.j = condis(str, &tmp,  tmp.eq);
		checkslh(str, tmp.i, &tmp);
		/*tmp.eq = checkq(str, tmp.i, tmp.eq);
		if (((str[tmp.i] != '$') || (tmp.i != 0 && str[tmp.i] == '$'
			&& str[tmp.i - 1] == '\\')) || tmp.eq == 1)
			ret[tmp.j] = str[tmp.i];
		tmp.j = condi(str, tmp.i, tmp.j, tmp.eq);
		if ((str[tmp.i] == '$' && tmp.eq == 2)
			|| (str[tmp.i] == '$' && tmp.eq == 0))
		{
			if ((tmp.i = ccg(str, &tmp, ret, cnf)) == -1)
				break ;
		}*/
		tmp.j++;
		tmp.i++;
	}
	ret[tmp.j] = 0;
	return (ret);
}
