/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:17:03 by eros-gir          #+#    #+#             */
/*   Updated: 2023/01/30 10:15:44 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<limits.h>
#include<stdio.h>

long int	ft_atol(const char *nptr)
{
	int			len;
	int			sign;
	long int	result;

	len = 0;
	sign = 1;
	result = 0;
	while (nptr[len] == ' ' || nptr[len] == '\n' || nptr[len] == '\t'
		|| nptr[len] == '\v' || nptr[len] == '\r' || nptr[len] == '\f')
		len++;
	if (nptr[len] == '-' || nptr[len] == '+')
	{
		if (nptr[len++] == '-')
			sign *= -1;
	}
	while (nptr[len] >= 48 && nptr[len] <= 57)
	{
		result = (nptr[len] - 48) + (result * 10);
		len++;
	}
	result = result * sign;
	return (result);
}
