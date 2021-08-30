
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *a;

	if (!(a = malloc(nmemb * size)))
		return (NULL);
	ft_bzero(a, nmemb * size);
	return (a);
}
