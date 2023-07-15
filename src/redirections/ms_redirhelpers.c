/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirhelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:08:43 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/15 18:16:55 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

size_t	ft_qstrnum(const char *s, char c, int qflags)
{
	size_t	len;
	size_t	numb;

	len = 0;
	numb = 0;
	while (s[len])
	{
		while (qflags && s[len])
		{
			qflags = msh_quote_flag(s[len], qflags);
			len++;
		}
		while (s[len] == c)
			len++;
		if (s[len] && s[len] != c)
		{
			numb++;
			qflags = msh_quote_flag(s[len], qflags);
		}
		while (s[len] != 0 && (s[len] != c))
			len++;
	}
	return (numb);
}

char	*ft_qstrset(const char *s, char c, int qflags)
{
	char	*sr;
	size_t	len;

	len = 0;
	while ((s[len] != c || qflags) && s[len])
	{
		qflags = msh_quote_flag(s[len], qflags);
		len++;
	}
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while ((s[len] != c || qflags) && s[len])
	{
		qflags = msh_quote_flag(s[len], qflags);
		sr[len] = s[len];
		len++;
	}
	sr[len] = '\0';
	return (sr);
}

//start qflag always at 0
char	**ft_qsplit(const char *s, char c, size_t n, int qflags)
{
	char	**strings;
	size_t	strn;

	strn = ft_qstrnum(s, c, 0);
	strings = ft_calloc(sizeof(char **), strn + 1);
	if (!strings)
		return (0);
	while (n < strn)
	{
		qflags = msh_quote_flag(*s, qflags);
		while (*s == c && !qflags)
			s++;
		strings[n] = ft_qstrset(s, c, qflags);
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
