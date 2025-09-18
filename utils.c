#include "pipex.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static int	add_word(char **tab, char *s, int j, char c)
{
	int	i;
	int	k;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	tab[j] = malloc(sizeof(char) * (i + 1));
	if (!tab[j])
		return (-1);
	k = 0;
	while (k < i)
	{
		tab[j][k] = s[k];
		k++;
	}
	tab[j][k] = 0;
	return (i);
}

static char	**process_words(char **tab, char *s, char c)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word_len = add_word(tab, &s[i], j, c);
			if (word_len == -1)
			{
				while (j > 0)
					free(tab[--j]);
				free(tab);
				return (NULL);
			}
			i += word_len;
			j++;
		}
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = count_words((char *) s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = 0;
	return (process_words(tab, (char *)s, c));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if (n && *s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*res;
	char		*start;
	const char	*p1;
	const char	*p2;

	p1 = s1;
	p2 = s2;
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	start = res;
	while (*p1)
		*res++ = *p1++;
	while (*p2)
	*res++ = *p2++;
	*res = '\0';
	return (start);
}
////before was libft
void free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}


