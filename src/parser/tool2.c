/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:14:54 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/10 18:17:21 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				isredir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

static	int		rec(char *line, int i, int j, t_tok *tok)
{
	int endn;
	int eq;

	endn = 0;
	eq = 0;
	while (line[i] && i < j)
	{
		eq = checkq(line, i, eq);
		tok->func[endn] = line[i];
		i++;
		endn++;
	}
	tok->func[endn] = 0;
	return (i);
}

int				funcname(char *line, int i, t_tok *tok)
{
	int		endn;
	int		j;
	int		eq;

	endn = 0;
	j = i;
	eq = 0;
	while (line[j])
	{
		eq = checkq(line, j, eq);
		if (eq == 0 && issep(line[j]))
		{
			if (j == 0 || (j > 0 && line[j - 1] != '\\'))
				break ;
		}
		endn++;
		j++;
	}
	if (!(tok->func = malloc(sizeof(char) * endn + 1)))
		return (-1);
	i = rec(line, i, j, tok);
	return (i);
}
