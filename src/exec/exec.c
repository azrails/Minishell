/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:59:08 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/26 17:59:09 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	**argtomatrix(t_tok *pnt, t_config *cnf)
{
	char **args;
	t_arg *tmp;
	int j;
	int i;

	i = 1;
	j = countargs(pnt->arg);
	tmp = pnt->arg;
	if (!(args = malloc(sizeof(char *) * (j + 2))))
		return (NULL);
	args[0] = getname(cnf, pnt);
	if (!args || !args[0] || !args[0][0])
	{
		cnf->err = 1;
		return (NULL);
	}
	tmp = pnt->arg;
	while (tmp && i < j + 1)
	{
		args[i] = getstr(tmp, cnf->envl);
		if (!args[i] || !args[i][0])
			i--;
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

static	void	preex(t_config *cnf, t_tok *pnt)
{
	char **targ;
	int i;

	i = 0;
	targ = NULL;
	//printf("arg preex %s : %s : %d : %d\n\n",pnt->func, pnt->arg->sarg, cnf->pipe.i, cnf->pipe.pid[cnf->pipe.i]);
	targ = argtomatrix(pnt, cnf);
	if (pnt->func && !(ft_strcmp(pnt->func, "exit")) && (cnf->pipe.cp != 0 && cnf->pipe.i == 0))
		cnf->err = 2;
	if (pnt->func && !(ft_strcmp(pnt->func, "exit")) && cnf->err == 0)
		ft_exit(cnf, targ);
	else if (targ && pnt->func && isbuilt(pnt->func) && cnf->exit && cnf->err == 0)
		gobuiltin(cnf, pnt, targ);
	else if (pnt->func && cnf->exit && cnf->err == 0)
		cnf->excode = goexec(cnf, pnt, targ);
	tf(targ);
}

static	int		cyclerdir(t_tok *pnt, t_config *cnf)
{
	t_rdir	*tmp;

	if (pnt->rdir != 0)
	{
		while (pnt->ndir)
		{
			tmp = pnt->ndir;
			free(pnt->prdir);
			pnt->prdir = ft_strdup(tmp->prdir);
			pnt->rdir = tmp->type;
			if (pnt->rdir == 1)
			{
				if(!(inp(cnf, pnt)))
				return(0);
			}
			else if (pnt->rdir == 2 || pnt->rdir == 3)
			{
				if(!(dir(cnf, pnt)))
				return (0);
			}
			pnt->ndir = pnt->ndir->next;
			free(tmp);
		}
	}
	return (1);
}

int		pipedir(t_tok *pnt, t_config *cnf)
{
	int pipe;

	pipe = 0;
	if (pnt->rdir == 1)
	{
		if(!(inp(cnf, pnt)))
			return(0);
	}
	else if (pnt->rdir == 2 || pnt->rdir == 3)
	{
		if(!(dir(cnf, pnt)))
			return (0);
	}
	if (!cyclerdir(pnt, cnf))
		return (0);
	if (pnt->rdir == 0 && pnt->tsep == 1 && cnf->child == 0)
		pnt = gopipe(pnt, cnf);
	if (cnf->child != 2)
		preex(cnf, pnt);
	return (1);
}

void	exec(t_config *cnf)
{
	t_tok	*pnt;
	int		status;
	int		i;

	pnt = cnf->tok;
	while (pnt)
	{
		i = 0;
		cnf->pipe.cp = 0;
		cnf->err = 0;
		cnf->child = 0;
		pipedir(pnt, cnf);
		savefd(cnf);
		closefds(cnf);
		resetfds(cnf);
		if (cnf->pipe.cp != 0 && ((cnf->pipe.i != 0 &&
			cnf->pipe.pid[cnf->pipe.i - 1] == 0) || cnf->pipe.pid[cnf->pipe.i] == 0))
			exit(cnf->excode);
		if (cnf->pipe.cp != 0)
		{
			waitpid(-1, &status, 0);
			cnf->excode = WEXITSTATUS(status);
		}
		while (i < cnf->pipe.cp)
		{
			pnt = pnt->next;
			i++;
		}
		pnt = pnt->next;
	}
}