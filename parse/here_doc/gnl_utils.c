#include "../../mini_shell.h"

int	ft_find_line(char *buff)
{
	int	i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

/*char	*ft_substr(char const *s, unsigned int str, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (str > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - str))
		len = ft_strlen(s) - str;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (p);
	if (ft_strlen(s) <= str)
		len = 0;
	while (i < len && s[str + i] != '\0')
	{
		p[i] = s[str + i];
		++i;
	}
	p[i] = '\0';
	return (p);
}*/

size_t	gnl_strlen(const char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n] != '\0')
		++n;
	return (n);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;

	i = ft_strlen(s);
	p = malloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (p);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		++i;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = (gnl_strlen(s1) + gnl_strlen(s2) + 1);
	p = (char *)malloc(i * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		p[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		p[i + j] = s2[j];
		++j;
	}
	p[i + j] = '\0';
	free(s1);
	return (p);
}
