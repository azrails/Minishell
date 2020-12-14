/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:24:54 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 16:25:38 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		serr(t_config *cnf, char *line, int i)
{
	if ((line && line[0] == ';') || (line && line[0] == '|'))
	{
		cnf->excode = 258;
		if ((line[0] == ';' && line[i + 1]
			&& line[i + 1] != ';') || (line[0] == ';' && !line[i + 1]))
		{
			ft_putstr_fd("syntax error near unexpected token ';'\n", 2);
			return (1);
		}
		if ((line[0] == '|' && line[i + 1] && line[i + 1] != '|')
			|| (line[0] == '|' && !line[i + 1]))
		{
			ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

static	int		sclerr(t_config *cnf, char *line, int i)
{
	if (i != 0 && line[i] == ';' && line[i + 1] == ';'
		&& line[i - 1] != '\\')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token ';;'\n", 2);
		return (1);
	}
	if (i != 0 && line[i] == '|' && line[i + 1] == '|'
		&& line[i - 1] != '\\')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token '||'\n", 2);
		return (1);
	}
	if (i == 0 && line[i] == ';' && line[i + 1] == ';')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token ';;'\n", 2);
		return (1);
	}
	return (0);
}

int				checkunexp(t_config *cnf, char *line)
{
	int i;

	i = 0;
	if (line && line[0] == '\\' && line[1] == '\0')
	{
		ft_putstr_fd("\e[1;38;5;202msyntax error multiline command\e[0m\n", 2);
		cnf->excode = 127;
		return (1);
	}
	if (serr(cnf, line, i))
		return (1);
	while (line[i])
	{
		if (sclerr(cnf, line, i))
			return (1);
		if (i == 0 && line[i] == '|' && line[i + 1] == '|')
		{
			cnf->excode = 258;
			ft_putstr_fd("syntax error near unexpected token '||'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
