/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:59:07 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:34:57 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	src_s;
	size_t	dst_s;

	src_s = 0;
	dst_s = ft_strlen(dst);
	if (dstsize < dst_s)
	{
		src_s = ft_strlen(src);
		return (dstsize + src_s);
	}
	while (src[src_s] && dstsize > 0 && dst_s < dstsize - 1)
	{
		dst[dst_s] = src[src_s];
		src_s++;
		dst_s++;
	}
	dst[dst_s] = '\0';
	while (src[src_s])
	{
		src_s++;
		dst_s++;
	}
	return (dst_s);
}
