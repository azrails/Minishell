
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	i = 0;
	while (s[i] != '\0')
		i++;
	copy = (char*)malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
