/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:58:36 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/16 19:58:38 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	con(t_config *cnf, int x)
{
	if (x < 0)
	{
		ft_putstr_fd("\e[1;38;5;202merror: read line try again\e[0m\n", 2);
		cnf->excode = 127;
		return ;
	}
	else if (x == 0)
	{
		tf(cnf->env);
		freeenvl(cnf->envl);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

void			pars(t_config *cnf)
{
	char	*line;
	t_tok	*tok;
	int		x;

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	ft_putstr_fd("\e[1;38;5;47mminishell:\e[0m ", 2);
	line = NULL;
	if ((x = get_next_line(0, &line)) <= 0)
		con(cnf, x);
	cnf->excode = (cnf->sig.ctc == 1) ? cnf->sig.excode : cnf->excode;
	if (line && cnf->sig.ctc != 1)
	{
		if (close_quote(line))
		{
			ft_putstr_fd("\e[1;38;5;202msyntax error: not close quote\e[0m\n", 2);
			cnf->excode = 127;
			free(line);
			return ;
		}
		if (checkunexp(cnf, line))
		{
			free(line);
			return ;
		}
		cnf->tok = analys(line);
	}
	else
		free(line);
}

int				main(int argc, char **argv, char **env)
{
	t_config cnf;

	init(&cnf, env);
	cnf.excode = 0;
	while (cnf.exit)
	{
		cnf.sig.ctc = 0;
		cnf.sig.excode = 0;
		cnf.sig.cts = 0;
		cnf.tok = NULL;
		pars(&cnf);
		if (cnf.tok != NULL)
			exec(&cnf);
		freetok(cnf.tok);
	}
	tf(cnf.env);
	freeenvl(cnf.envl);
	write(1, "\0", 0);
	return (cnf.excode);
}
