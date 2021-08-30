
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (new)
	{
		new->next = NULL;
		new->content = content;
	}
	return (new);
}
