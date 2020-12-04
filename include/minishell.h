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
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"

typedef	struct  c_pipe
{
	int			cp;
}				t_pipe;

typedef	struct s_arg
{
	int			quote;// тип кавычек в которые взят аргумент 1 == ' & 2 == " & 0 == без кавычек
	char		*sarg;// кусочек аргумента до разделителя
	struct	s_arg	*next;
	struct	s_arg	*prev;
}				t_arg;

typedef	struct s_env
{
	char		*key;
	char		*value;
	struct  s_env	*next;
}				t_env;

typedef	struct  s_rdir
{
	int			type;
	char		*prdir;
	struct s_rdir *next;
}				t_rdir;

typedef	struct s_tok
{
	int			qfunc; //взята ли функция в кавычки
	int			rdir; //тип редиректа : 1 == < , 2 == > , 3 == >> , 0 == без редиректа
	int			tsep; //tip separator if ; => 0 if | => 1,2...n
	char		*prdir; // куда редирект
	char		*func; //имя функции
	t_rdir		*ndir;
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
	int			err;
	int			in;
	int			out;
	int			pipein;
	int			pipeout;
	int			savein;
	int			saveout;
	int			exit;
	int			excode; //код выхода
	char		**env;
	pid_t		pid;
	t_env		*envl;
	t_sig		sig;// сигналы
	t_tok		*tok;// список вызовов
}				t_config;

t_tok	*analys(char *line);
int		skipsep(t_tok *tok, char *line, int i);
int		redir(char *line, int i, t_tok *tok);
int		issep(char c);
void	exec(t_config *cnf);
int		inp(t_config *cnf, t_tok *pnt);
int		dir(t_config *cnf, t_tok *pnt);
void	resfds(t_config *cnf);
int		countargs(t_arg *arg);
void	init(t_config *cnf, char **env);
int		lenenv(t_env *env);
char	*getstr(t_arg *arg, t_env *env);
int		goexec(t_config *cnf, t_tok *pnt, char **targ);
void	tf(char **tab);
int		gobuiltin(t_config *cnf, t_tok *pnt, char **targ);
int		isbuilt(char *name);
void	closefd(int fd);
void	closefds(t_config *cnf);
void	resetfds(t_config *cnf);
void	savefd(t_config *cnf);
void	freetok(t_tok *tok);
void	freeenvl(t_env *env);
void	ft_exit(t_config *cnf, char **targ);
int		gopipe(t_tok *pnt, t_config *cnf);
char	*getname(t_config *cnf, t_tok *pnt);
int		isredir(char c);
int		addredir(t_tok *tok, int i, char *line);
# endif
