
int		ft_skipspace(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' ||
		line[i] == '\f')
		i++;
	return (i);
}
