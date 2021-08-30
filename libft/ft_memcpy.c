
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}
