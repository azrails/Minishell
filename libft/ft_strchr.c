
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = (char*)s;
	while (len >= 0)
	{
		if (*str == (char)c)
			return (str);
		str++;
		len--;
	}
	return (NULL);
}
