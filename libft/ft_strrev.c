/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:29:53 by eros-gir          #+#    #+#             */
/*   Updated: 2022/06/28 11:42:30 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrev(char *s)
{
	size_t	l;
	size_t	len;
	char	temp;

	len = ft_strlen(s);
	if (s[len] == '\0')
		len--;
	l = 0;
	while (l < len)
	{
		temp = s[l];
		s[l++] = s[len];
		s[len--] = temp;
	}
	return (s);
}
