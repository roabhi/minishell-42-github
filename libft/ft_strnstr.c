/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:26:26 by eros-gir          #+#    #+#             */
/*   Updated: 2022/01/13 15:58:37 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hs;
	size_t	ns;

	hs = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[hs] && hs < len)
	{
		ns = 0;
		while (haystack[hs + ns]
			&& haystack[hs + ns] == needle[ns]
			&& (hs + ns) < len)
		{
			if (needle[ns + 1] == '\0')
				return ((char *)(haystack + hs));
			ns++;
		}
		hs++;
	}
	return (0);
}
