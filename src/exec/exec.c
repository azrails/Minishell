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
	args[0] = ft_strdup(pnt->func);
	//args[0] = getname(cnf, pnt);
	while (tmp && i < j + 1)
	{
		args[i] = getstr(tmp, cnf->envl);
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
	targ = argtomatrix(pnt, cnf);
	if (pnt->func && !(ft_strcmp(pnt->func, "exit")))
		ft_exit(cnf, targ);
	else if (targ && pnt->func && isbuilt(pnt->func) && cnf->exit)
		gobuiltin(cnf, pnt, targ);
	else if (pnt->func && cnf->exit)
		cnf->excode = goexec(cnf, pnt, targ);
	tf(targ);
}

static	int		pipedir(t_tok *pnt, t_config *cnf)
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
	if (pnt->rdir == 0 && pnt->tsep == 1)
		gopipe(pnt, cnf);
	preex(cnf, pnt);
	return (1);
}

void	exec(t_config *cnf)
{
	t_tok	*pnt;
	int		status;

	pnt = cnf->tok;
	while (pnt)
	{
		pipedir(pnt, cnf);
		savefd(cnf);
		closefds(cnf);
		resetfds(cnf);
		waitpid(-1, &status, 0);
		//if (WIFEXITED(status))
			//cnf->excode = WEXITSTATUS(status);
		//else
		//	cnf->excode = 1;*/
		pnt = pnt->next;
	}
}