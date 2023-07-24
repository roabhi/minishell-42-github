/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:12:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/24 20:54:43 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			l;
	unsigned char	*s;
	unsigned char	*d;

	l = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (!s && !d)
		return (NULL);
	if (n != 0)
	{
		while (l < n)
		{
			d[l] = s[l];
			l++;
		}
	}
	return (dst);
}
