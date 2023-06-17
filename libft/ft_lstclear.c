/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:48:13 by eros-gir          #+#    #+#             */
/*   Updated: 2022/08/03 15:51:02 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(int *))
{
	t_list	*lstn;

	while (lst && *lst)
	{
		lstn = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lstn;
	}
}
