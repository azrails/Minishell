
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	i = -1;
	if ((!dest && !src) || !n)
		return (dest);
	if (dest < src)
		while (++i < n)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	else
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}
