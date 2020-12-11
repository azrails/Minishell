/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toks2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:21:52 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/10 18:25:34 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int				argqt(t_arg *arg, char *line, int i)
{
	arg->quote = 0;
	if (line[i] == '\'')
		arg->quote = 1;
	if (line[i] == '\"')
		arg->quote = 2;
	return (i);
}

static	int				dr(char *line, int i, int j, t_arg *arg)
{
	int	arglen;
	int q;

	arglen = 0;
	q = i;
	while (line[q] && q < j)
	{
		arg->sarg[arglen] = line[q];
		q++;
		arglen++;
	}
	i = j;
	arg->sarg[arglen] = 0;
	return (i);
}

static	int				checkbreak(char *line, int j, int eq)
{
	if (issep(line[j]) && eq == 0)
	{
		if (j == 0 || (j > 0 && line[j - 1] != '\\'))
			return (1);
	}
	if (eq == 0 && isredir(line[j]))
		return (1);
	return (0);
}

t_arg					*getarg(char *line, int *i)
{
	t_arg	*arg;
	int		arglen;
	int		j;
	int		eq;

	arglen = 0;
	if (!(arg = malloc(sizeof(t_arg))))
		return (NULL);
	arg->next = NULL;
	arg->prev = NULL;
	*i = argqt(arg, line, *i);
	eq = 0;
	j = *i;
	while (line[j])
	{
		eq = checkq(line, j, eq);
		if (checkbreak(line, j, eq))
			break ;
		arglen++;
		j++;
	}
	if (!(arg->sarg = malloc(sizeof(char) * arglen + 1)))
		return (NULL);
	*i = dr(line, *i, j, arg);
	return (arg);
}
