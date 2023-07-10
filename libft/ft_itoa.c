/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:23:38 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/10 15:33:44 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_getintsize(int n)
{
	size_t	count;

	count = 0;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_revstr(char *s)
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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	ft_sign(int n)
{
	if (n < 0)
		return ('-');
	return ('\0');
}

char	*ft_itoa(int n)
{
	char	*itoa;
	size_t	len;
	char	sign;
	size_t	l;

	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = ft_sign(n);
	n = ft_abs(n);
	len = ft_getintsize(n);
	itoa = ft_calloc(sizeof(char), len + 2);
	l = 0;
	if (!itoa)
		return (0);
	itoa[0] = '0';
	while (l < len)
	{
		itoa[l++] = (n % 10) + 48;
		n = n / 10;
	}
	if (sign)
		itoa[l] = sign;
	return (ft_revstr(itoa));
}
