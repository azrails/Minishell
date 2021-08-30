
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	elem = *lst;
	if (lst == NULL || *lst == NULL)
		*lst = new;
	else
	{
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
	}
}
