/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:19:42 by eros-gir          #+#    #+#             */
/*   Updated: 2022/04/12 10:25:32 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*sr;
	size_t	slen;
	size_t	flen;

	if (!s1 || !set)
		return (0);
	slen = 0;
	while (s1[slen] && ft_strchr((char *)set, s1[slen]))
		slen++;
	flen = ft_strlen(s1);
	while (flen > slen && ft_strchr((char *)set, s1[flen]))
		flen--;
	if (slen > flen)
		return (ft_strdup(""));
	sr = ft_substr(s1, slen, flen - slen + 1);
	return (sr);
}
