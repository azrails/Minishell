
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = (char*)s;
	str += len;
	while (len >= 0)
	{
		if (*str == (char)c)
			return (str);
		str--;
		len--;
	}
	return (NULL);
}
