
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*newstr;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(newstr = (char*)malloc(sizeof(char) + (len + 1))))
		return (NULL);
	while (*s1 != '\0')
	{
		newstr[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		newstr[i] = *s2++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
