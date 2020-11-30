/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toks.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:03:53 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/21 20:03:55 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		funcname(char *line, int i, t_tok *tok)
{
	int		endn;
	int		j;
	int		oq;
	
	endn = 0;
	j = i;
	oq = 0;
	while (line[j])
	{
		if (line[i] == '\'' && oq == 0)
			oq = 1;
		if (line[i] == '\"' && oq == 0)
			oq = 2;
		if (line[i] == '\'' && oq == 1)
			oq = 0;
		if (line[i] == '\"' && oq == 2)
			oq = 0;
		if (oq == 0 && (line[j] == ' ' || line[j] == '|' || line[j] == ';'))
			break;
		if (oq == 0 && (line[i] == '\''|| line[i] == '\"'))
			endn--;
		endn++;
		j++;
	}
	if(!(tok->func = malloc(sizeof(char) * endn + 1)))
		return (-1);
	endn = 0;
	while (line[i] && i < j)
	{
		if (line[i] == '\'' && oq == 0)
			oq = 1;
		if (line[i] == '\"' && oq == 0)
			oq = 2;
		if (line[i] == '\'' && oq == 1)
			oq = 0;
		if (line[i] == '\"' && oq == 2)
			oq = 0;
		tok->func[endn] = line[i];
		if (oq == 0 && (line[i] == '\''|| line[i] == '\"'))
			endn--;
		i++;
		endn++;
	}
	tok->func[endn] = 0;
	return (i);
}

static	int		argqt(t_arg *arg, char *line, int i)
{
	arg->quote = 0;
	if (line[i] == '\'')
		arg->quote = 1;
	if (line[i] == '\"')
		arg->quote = 2;
	return (i);
}

static	t_arg	*getarg(char *line, int *i)
{
	t_arg *arg;
	int		arglen;
	int		j;
	int		eq;
	int		q;
	
	arglen = 0;
	if (!(arg = malloc(sizeof(t_arg))))
		return (NULL);
	arg->next = NULL;
	arg->prev = NULL;
	*i = argqt(arg, line, *i);
	eq = arg->quote;
	if (eq != 0)
		*i += 1;
	j = *i;
	while (line[j])
	{
		if (issep(line[j]) && eq == 0)
			break;
		if ((line[j] == '\'' && eq == 1))
			eq = 0;
		if ((line[j] == '\"' && eq == 2))
			eq = 0;
		arglen++;
		j++;
	}
	if (!(arg->sarg = malloc(sizeof(char) * arglen + 1)))
		return (NULL);
	arglen = 0;
	eq = arg->quote;
	q = *i;
	while (line[*i] && q < j)
	{
		arg->sarg[arglen] = line[q];
		q++;
		arglen++;
	}
	*i = j;
	if (eq == 0)
		arg->sarg[arglen] = 0;
	if (eq != 0)
		arg->sarg[arglen - 1] = 0;
	return (arg);
}

static	int		args(char *line, int i, t_tok *tok)
{
	t_arg *farg;
	t_arg *sarg;

	farg = NULL;
	sarg = NULL;
	while (line[i])
	{
		i = ft_skipspace(line, i);
		if (line[i] == '\0' || issep(line[i]))
			break;
		if(!(farg = getarg(line, &i)))
			return (-1);
		farg->prev = sarg;
		if (sarg)
			sarg->next = farg;
		sarg = farg;
	}
	while (farg && farg->prev)
		farg = farg->prev;
	tok->arg = farg;
	return (i);
}

static	t_tok	*newtok(char *line, int *i)
{
	t_tok	*tok;

	if (!(tok = malloc(sizeof(t_tok))))
		return(NULL);
	tok->rdir = 0;
	tok->arg = NULL;
	tok->next = NULL;
	tok->prdir = NULL;
	if ((*i = funcname(line, *i, tok)) < 0)
		return (NULL);
	while (line[*i])
	{
		*i = ft_skipspace(line, *i);
		if (issep(line[*i]))
			break;
		if ((*i = redir(line, *i, tok)) < 0)
			return (NULL);
		if (line[*i] == ';' || line[*i] == '|')
			break;
		if ((*i = args(line, *i, tok)) < 0)
			return (NULL);
		if (issep(line[*i]))
			break;
	}
	return (tok);
}

t_tok	*analys(char *line)
{
	int		i;
	t_tok	*ftok;
	t_tok	*stok;

	i = 0;
	stok = NULL;
	ftok = NULL;
	i = ft_skipspace(line, i);
	while (line[i])
	{
		if (stok)
			i = skipsep(stok, line, i);
		if (line[i] == '\0')
			break;
		ftok = newtok(line, &i);// добавить фцию которая в случае неудачи удаляет весь список
		ftok->prev = stok;
		if (stok)
			stok->next = ftok;
		stok = ftok;
		i = ft_skipspace(line, i);
	}
	while (ftok && ftok->prev)
		ftok = ftok->prev;
	free(line);
	return (ftok);
}
