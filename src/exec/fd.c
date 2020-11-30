/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:58:06 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/30 22:58:08 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	savefd(t_config *cnf)
{
	cnf->savein = dup(cnf->in);
	cnf->saveout = dup(cnf->saveout);
}

void	closefds(t_config *cnf)
{
	closefd(cnf->pipein);
	closefd(cnf->pipeout);
	closefd(cnf->in);
	closefd(cnf->out);
}

void	resetfds(t_config *cnf)
{
	dup2(cnf->savein, cnf->in);
	dup2(cnf->saveout, cnf->out);
	cnf->pipein = -1;
	cnf->pipeout = -1;
}

void	closefd(int fd)
{
	if (fd > 0)
		close(fd);
}
