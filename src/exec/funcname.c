/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:48:55 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 00:39:48 by wsallei          ###   ########.fr       */
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

static	int			ccg(t_tok *pnt, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (pnt->func[tmp->i + 1] && pnt->func[tmp->i + 1] == '?')
	{
		gtc(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(pnt->func, cnf->envl, tmp, ret);
		if (pnt->func[tmp->i] == '\0')
			return (-1);
		tmp->i--;
	}
	return (tmp->i);
}

static	int			condi(t_tok *pnt, int i, int j, int eq)
{
	if ((i == 0 && pnt->func[i] == '\\' && eq == 0) || (i != 0 &&
		(pnt->func[i] == '\\' && pnt->func[i - 1] != '\\') && eq == 0))
		j--;
	if ((pnt->func[i] == '\'' || pnt->func[i] == '\"') && eq == 0)
	{
		if (i != 0 && pnt->func[i - 1] != '\\')
			j--;
	}
	if (pnt->func[i] == '\'' && eq == 1)
	{
		if (i != 0 && pnt->func[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	if (pnt->func[i] == '\"' && eq == 2)
	{
		if (i != 0 && pnt->func[i - 1] != '\\')
			j--;
		if (i == 0)
			j--;
	}
	return (j);
}

static	void		ii(t_tmp *tmp, t_config *cnf, t_env *env)
{
	tmp->i = 0;
	tmp->j = 0;
	tmp->eq = 0;
	env = cnf->envl;
}

char				*namefunc(t_config *cnf, t_tok *pnt, int len)
{
	t_env	*env;
	char	*ret;
	t_tmp	tmp;

	ii(&tmp, cnf, env);
	ret = malloc(sizeof(char) * len + 1);
	while (pnt->func[tmp.i])
	{
		tmp.eq = checkq(pnt->func, tmp.i, tmp.eq);
		if (((pnt->func[tmp.i] != '$') || (tmp.i != 0 && pnt->func[tmp.i] == '$'
			&& pnt->func[tmp.i - 1] == '\\')) || tmp.eq == 1)
			ret[tmp.j] = pnt->func[tmp.i];
		tmp.j = condi(pnt, tmp.i, tmp.j, tmp.eq);
		if ((pnt->func[tmp.i] == '$' && tmp.eq == 2)
			|| (pnt->func[tmp.i] == '$' && tmp.eq == 0))
		{
			if ((tmp.i = ccg(pnt, &tmp, ret, cnf)) == -1)
				break ;
		}
		tmp.j++;
		tmp.i++;
	}
	ret[tmp.j] = 0;
	return (ret);
}
