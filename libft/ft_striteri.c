/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:23:38 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:34:52 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(const char *s, void (*f)(unsigned int, char*))
{
	size_t	len;

	len = 0;
	while (len < ft_strlen(s))
	{
		f(len, (char *)s + len);
		len++;
	}
}
