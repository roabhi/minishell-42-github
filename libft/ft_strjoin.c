/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:08:45 by eros-gir          #+#    #+#             */
/*   Updated: 2022/05/18 11:11:02 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	char	*sr;
	int		secur;

	l1 = -1;
	l2 = -1;
	secur = 0;
	if (!s1)
	{
		s1 = ft_calloc(sizeof(char), 2);
		s1[0] = '\0';
		secur = 1;
	}
	sr = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sr)
		return (0);
	while (s1[++l1])
		sr[l1] = s1[l1];
	while (s2[++l2])
		sr[l1 + l2] = s2[l2];
	sr[l1 + l2] = '\0';
	if (secur)
		free(s1);
	return (sr);
}
