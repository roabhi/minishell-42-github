/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:19:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:34:42 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnum(const char *s, char c)
{	
	size_t	len;
	size_t	numb;

	len = 0;
	numb = 0;
	while (s[len])
	{
		while (s[len] == c)
			len++;
		if (s[len] && s[len] != c)
			numb++;
		while (s[len] != 0 && (s[len] != c))
			len++;
	}
	return (numb);
}

char	*ft_strset(const char *s, char c)
{
	char	*sr;
	size_t	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len] != c && s[len])
	{
		sr[len] = s[len];
		len++;
	}
	sr[len] = '\0';
	return (sr);
}

char	**ft_split(const char *s, char c)
{
	char	**strings;
	size_t	n;
	size_t	strn;

	n = 0;
	strn = ft_strnum(s, c);
	strings = ft_calloc(sizeof(char **), strn + 1);
	if (!strings)
		return (0);
	while (n < strn)
	{
		while (*s == c)
			s++;
		strings[n] = ft_strset(s, c);
		if (!strings[n])
		{
			while (n > 0)
				free(strings[--n]);
			free(strings);
			return (0);
		}
		s += ft_strlen(strings[n++]);
	}
	strings[n] = 0;
	return (strings);
}
