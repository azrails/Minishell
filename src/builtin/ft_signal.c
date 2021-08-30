#include "../../include/minishell.h"

void	ft_signalc(int signal)
{
	if (signal == SIGINT)
	{
		if (!g_sig.pid)
		{
			ft_putstr_fd("\b\b  \b\b\n", 2);
			ft_putstr_fd("\e[1;38;5;47mminishell:\e[0m ", 2);
			g_sig.excode = 1;
		}
		else
		{
			ft_putstr_fd("\n", 2);
			g_sig.excode = 130;
		}
		g_sig.ctc = 1;
	}
}

void	ft_signals(int signal)
{
	if (signal == SIGQUIT)
	{
		if (g_sig.pid != 0)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			g_sig.cts = 1;
			g_sig.excode = 131;
		}
		else
			ft_putstr_fd("\b\b  \b\b", 2);
	}
}
