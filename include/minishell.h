/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:09:15 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/16 20:19:14 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

#include <stdio.h>//////delete

# include <signal.h>
# include "../libft/libft.h"

typedef	struct s_arg
{
	int			quote;// тип кавычек в которые взят аргумент 1 == ' & 2 == " & 0 == без кавычек
	char		*sarg;// кусочек аргумента до разделителя
	struct	s_arg	*next;
	struct	s_arg	*prev;
}				t_arg;

typedef	struct s_tok
{
	int			cfunc; //код функции тип echo == 1, итд возможно оно и не нужно
	int			rdir; //тип редиректа : 1 == < , 2 == > , 3 == >> , 0 == без редиректа
	int			tsep; //tip separator if ; => 0 if | => 1,2...n
	char		*prdir; // куда редирект
	char		*func; //имя функции
	t_arg		*arg; //список аргументов
	struct	s_tok	*next;
	struct	s_tok	*prev;
}				t_tok;

typedef	struct	s_sig
{
	int			ctc; //ctrl-C
	int			cts; //ctrl-/
	int			ctd; //ctrl-D
}				t_sig;

typedef	struct	s_config
{
	int			exit;
	int			excode; //код выхода
	t_sig		sig;// сигналы
	t_tok		*tok;// список вызовов
}				t_config;

t_tok	*analys(char *line);
int		skipsep(t_tok *tok, char *line, int i);
int		redir(char *line, int i, t_tok *tok);
int		issep(char c);
# endif
