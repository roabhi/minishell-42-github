/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:42:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:35:17 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrcmp(const char *str1, const char *str2, size_t n)
{
	size_t			l[4];
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	l[0] = ft_strlen((const char *)s1);
	l[1] = ft_strlen((const char *)s2);
	l[2] = l[0];
	l[3] = l[1];
	if (n == 0)
		return (0);
	while (s1[l[0]] == s2[l[1]] && l[0] > l[2] - n && l[1] > l[3] - n
		&& l[0] > 0 && l[1] > 0)
	{
		l[0]--;
		l[1]--;
		if ((l[1] == 0 && l[0] != 0) || (l[1] != 0 && l[0] == 0))
			return (1);
	}
	return (s1[l[0]] - s2[l[1]]);
}
