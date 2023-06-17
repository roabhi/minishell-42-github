/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:08:45 by eros-gir          #+#    #+#             */
/*   Updated: 2022/05/18 11:06:10 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

//the two arguments given must be memory allocated not pointers to stack
char	*ft_joinloc(char *s1, char *s2)
{
	int		l1;
	int		l2;
	char	*sr;

	l1 = -1;
	l2 = -1;
	sr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sr)
	{
		free(s1);
		free(s2);
		return (0);
	}
	while (s1[++l1])
		sr[l1] = s1[l1];
	while (s2[++l2])
		sr[l1 + l2] = s2[l2];
	sr[l1 + l2] = '\0';
	free(s1);
	free(s2);
	return (sr);
}
