
#include "../../include/minishell.h"

int			ft_pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (errno);
}
