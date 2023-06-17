/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:03:55 by eros-gir          #+#    #+#             */
/*   Updated: 2022/01/20 10:11:15 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			l;
	unsigned char	p;
	unsigned char	*str;

	l = 0;
	str = (unsigned char *)s;
	if (n == 0)
		return (0);
	p = (unsigned char)c;
	while (l < n)
	{
		if (str[l] == p)
			return (((void *)s) + l);
		l++;
	}
	return (0);
}
