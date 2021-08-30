
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len && *big)
	{
		i = ft_strlen(little);
		while (*big && i <= len--)
			if (!(ft_strncmp(big++, little, i)))
				return ((char *)--big);
	}
	return (NULL);
}
