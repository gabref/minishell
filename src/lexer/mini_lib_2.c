#include "../../inc/lexer.h"

void	*ft_memcpy_lex(void *dest, void *src, int n)
{
	int				i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

// char	*ft_strdup(const char *src) // modificata
// {
// 	char *dest;
//
// 	int i;
//
// 	i = 0;
//
// 	dest = (char *)malloc((sizeof(char)) * (ft_strlen_lex((char *)src) + 1));
// 		// modificato
// 	if (dest == NULL)
// 		return (0);
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

void	*ft_memset(void *b, int c, size_t len) // modificata
{
	unsigned char *ptr;

	ptr = b;

	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

int	strchr_lex(char *str, char c)

{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}
