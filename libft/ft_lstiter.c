/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:48:13 by eros-gir          #+#    #+#             */
/*   Updated: 2022/08/03 16:09:44 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int *))
{
	while (lst)
	{
		f(&lst->content);
		lst = lst->next;
	}
}

void	ft_lstiter_put(t_list *lst)
{
	while (lst)
	{
		ft_putnbr_fd(lst->content, 1);
		ft_putchar_fd('\t', 1);
		lst = lst->next;
	}
	ft_putchar_fd('\n', 1);
}
