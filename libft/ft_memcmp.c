/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:30:52 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:34:17 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			l;
	unsigned char	*str1;
	unsigned char	*str2;

	l = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[l] == str2[l] && l < n - 1)
		l++;
	if (l == n)
		return (0);
	else
		return (str1[l] - str2[l]);
}
