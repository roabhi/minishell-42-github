/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:42:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:35:08 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			l;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	l = 0;
	if (n == 0)
		return (0);
	while (s1[l] == s2[l] && l < n - 1)
	{
		if (!s2[l] || !s1[l])
			break ;
		l++;
	}
	return (s1[l] - s2[l]);
}
