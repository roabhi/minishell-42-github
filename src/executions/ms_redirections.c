/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/26 18:25:08 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_is_redirect(t_cmd tcmd)
{
	if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], "<") == 0)
	{
		write(2, "Redirect\n", 9);
		return (1);
	}
	else if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], ">") == 0)
		return (2);
	return (0);
}

int	msh_exec_redirect(t_cmd *cmd, int fd)
{
	if (msh_is_redirect(*cmd->next) == 1)
		fd = open(cmd->next->next->argv[0], O_RDONLY);
	else if (msh_is_redirect(*cmd->next) == 2)
		fd = open(cmd->next->next->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}