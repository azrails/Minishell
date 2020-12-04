/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:28:06 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/04 12:28:08 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		isredir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return(0);
}

static	int		typedir(char *line, int i)
{
	int	type;

	type = 0;
	if (line[i] == '<')
		type = 1;
	else if (line[i] && (line[i] == '>' && line[i + 1] == '>'))
		type = 3;
	else if (line[i] == '>')
		type = 2;
	return (type);
}

static	int		checkq(char c, int oq)
{
	if (c == '\'' && oq == 0)
			oq = 1;
	if (c == '\"' && oq == 0)
			oq = 2;
	if (c == '\'' && oq == 1)
			oq = 0;
	if (c == '\"' && oq == 2)
			oq = 0;
	return (oq);
}

static	int getpth(t_rdir *tmp, char *line, int i)
{
	int j;
	int	oq;
	int	count;

	oq = 0;
	count = 0;
	i = ft_skipspace(line, i);
	j = i;
	while (line[j])
	{
		oq = checkq(line[j], oq);
		if ((oq == 0 && line[j] == ' ') || (oq == 0  && line[j] == '|' ) || (oq == 0 && line[j] == ';'))
			break;
		if (oq == 0 && (line[i] == '\''|| line[i] == '\"'))
			count--;
		count++;
		j++;
	}
	tmp->prdir = malloc(sizeof(char) * count + 1);
	count = 0;
	while (line[i] && i < j)
	{
		oq = checkq(line[j], oq);
		tmp->prdir[count] = line[i];
		if (oq == 0 && (line[i] == '\''||line[i] == '\"'))
			count--;
		count++;
		i++;
	}
	tmp->prdir[count] = 0;
	return (i);
}

int		addredir(t_tok *tok, int i, char *line)
{
	t_rdir	*tmp;
	t_rdir	*sc;

	if (!tok->prdir)
		i = redir(line, i, tok);
	else
	{
		sc = tok->ndir;
		while (sc && sc->next)
			sc = sc->next;
		if(!(tmp = malloc(sizeof(t_rdir))))
			return (i);
		tmp->type = typedir(line, i);
		if (tmp->type == 1 || tmp->type == 2)
			i++;
		else
			i+=2;
		i = getpth(tmp ,line, i);
		tmp->next = NULL;
		if (sc)
			sc->next = tmp;
		else
			tok->ndir = tmp;
	}
	return (i);
}