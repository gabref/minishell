#include "../../inc/lexer.h"

int	ft_strlen_lex(char *s)

{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp_lex(char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i < (n - 1) && *s1 == *s2)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] || fd < 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_substr_lex(char *s, int start, int len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > ft_strlen_lex(s))
		len = ft_strlen_lex(s);
	if (start >= ft_strlen_lex(s))
		return (ft_strdup(""));
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy_lex(ptr, s + start, len);
	ptr[len] = '\0';
	return (ptr);
}
