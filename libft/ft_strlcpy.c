/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:05:22 by eros-gir          #+#    #+#             */
/*   Updated: 2022/01/13 14:51:23 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	l;
	size_t	srclen;

	srclen = ft_strlen(src);
	l = 0;
	if (dstsize != 0)
	{
		while (src[l] && l < dstsize - 1)
		{
			dst[l] = src[l];
			l++;
		}
	dst[l] = '\0';
	}
	return (srclen);
}
