
#include "libft.h"

static int	countlen(int n)
{
	int i;

	i = 1;
	if (n < 0)
		i++;
	while (n /= 10)
	{
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = countlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		if (n < 0)
			str[--len] = (n % 10) * -1 + '0';
		if (n > 0)
			str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
