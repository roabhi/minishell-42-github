/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:48:13 by eros-gir          #+#    #+#             */
/*   Updated: 2022/08/03 15:58:01 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(int *), void (*del)(int *))
{
	t_list	*tempcont;
	t_list	*nlst;

	nlst = 0;
	while (lst)
	{
		tempcont = ft_lstnew((int)f(&lst->content));
		if (!tempcont)
		{
			ft_lstclear(&nlst, del);
			return (0);
		}
		ft_lstadd_back(&nlst, tempcont);
		lst = lst->next;
	}
	return (nlst);
}
