/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:23:38 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:35:05 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*sr;

	len = 0;
	sr = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!sr)
		return (0);
	while (len < ft_strlen(s))
	{
		sr[len] = f(len, s[len]);
		len++;
	}
	sr[len] = '\0';
	return (sr);
}
