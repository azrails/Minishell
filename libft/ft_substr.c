
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (!(sub = ((char*)malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	while (s[start] && len > 0)
	{
		sub[i++] = s[start++];
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
