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

int		close_quote(char *line)
{
	int i;
	int type;

	type = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] == '\'' && type == 0)
		{
			if (i > 0 && line[i - 1] == '\\')
				type = 0;
			else
				type = 1;
		}
		else if (line[i] == '\"' && type == 0)
		{
			if (i > 0 && line[i - 1] == '\\')
				type = 0;
			else
				type = 2;
		}
		else if (line[i] == '\'' && type == 1)
			type = 0;
		else if (line[i] == '\"' && type == 2)
		{
			if (i > 0 && line[i - 1] == '\\')
				type = 2;
			else
				type = 0;
		}
		i++;
	}
	return (type);
}

int		checkunexp(t_config *cnf, char *line)
{
	int i;

	i = 0;
	if ((line && line[0] == ';') || (line && line[0] == '|'))
	{
		cnf->excode = 258;
		if ((line[0] == ';' && line[i + 1] && line[i + 1] != ';') || (line[0] == ';' && !line[i + 1]))
		{
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m ';'\n",2);
			free(line);
			return (1);
		}
		if ((line[0] == '|' && line[i + 1] && line[i + 1] != '|') || (line[0] == '|' && !line[i + 1]))
		{
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m '|'\n",2);
			free(line);
			return (1);
		}
	}
	while (line[i])
	{
		if (i != 0 && line[i] == ';' && line[i + 1] == ';' && line[i - 1] != '\\')
		{
			cnf->excode = 258;
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m ';;'\n", 2);
			free(line);
			return (1);
		}
		if (i != 0 && line[i] == '|' && line[i + 1] == '|' && line[i - 1] != '\\')
		{
			cnf->excode = 258;
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m '||'\n", 2);
			free(line);
			return (1);
		}
		if (i == 0 && line[i] == ';' && line[i + 1] == ';')
		{
			cnf->excode = 258;
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m ';;'\n", 2);
			free(line);
			return (1);
		}
		if (i == 0 && line[i] == '|' && line[i + 1] == '|')
		{
			cnf->excode = 258;
			ft_putstr_fd("\e[1;38;5;202msyntax error near unexpected token\e[0m '||'\n", 2);
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}

void	pars(t_config *cnf)
{
	char *line;
	int i = 0;
	t_tok	*tok;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_putstr_fd("\e[1;38;5;47mminishell:\e[0m ", 2);
	if(get_next_line(0 ,&line) < 0)/////ctrl-d == eof => когда из гнл приходит 0 надо выходить из шела
	{
		ft_putstr_fd("\e[1;38;5;202merror: read line try again\e[0m\n", 2);
		cnf->excode = 127;
		return ;
	}
	if(close_quote(line))
	{
		ft_putstr_fd("\e[1;38;5;202msyntax error: not close quote\e[0m\n", 2);
		cnf->excode = 127;
		free(line);
		return ;
	}
	if(checkunexp(cnf, line))
		return	;
	cnf->tok = analys(line);

	t_tok *ptf;
	t_arg *tmp;
	ptf = cnf->tok;
	/*while (ptf)
	{
		printf("type tsep %d , type rdir %d , func %s , path rdir %s \n",ptf->tsep, ptf->rdir, ptf->func, ptf->prdir);
		tmp = ptf->arg;
		while (tmp)
		{
			printf("type quote %d , args %s\n\n",tmp->quote, tmp->sarg);
			tmp  = tmp->next;
		}
		ptf = ptf->next; 
	}*/
}

int		main(int argc, char **argv, char **env)
{
	t_config cnf;

	init(&cnf, env);
	cnf.excode = 0;
	while(cnf.exit)
	{
		cnf.sig.ctc = 0;
		cnf.sig.ctd = 0;
		cnf.sig.cts = 0;
		cnf.tok = NULL;
		pars(&cnf);
		if (cnf.tok != NULL)
			exec(&cnf);
		freetok(cnf.tok);
	}
	tf(cnf.env);
	freeenvl(cnf.envl);
	return (cnf.excode);
}