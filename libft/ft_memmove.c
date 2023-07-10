/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:12:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:34:26 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			l;
	unsigned char	*s;
	unsigned char	*d;

	l = -1;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (!s && !d)
		return (NULL);
	if (d < s)
	{
		if (len != 0)
		{
			while (++l < len)
				d[l] = s[l];
		}
	}
	else
	{
		while (len--)
			d[len] = s[len];
	}
	return (dst);
}
