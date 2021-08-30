
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;

	if (lst && del)
	{
		while (*lst != NULL)
		{
			elem = *lst;
			*lst = elem->next;
			del(elem->content);
			free(elem);
		}
	}
}
