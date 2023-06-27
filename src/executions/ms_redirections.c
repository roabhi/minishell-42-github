/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/27 17:41:56 by eros-gir         ###   ########.fr       */
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

int	msh_exec_redirect(t_cmd *cmd)
{
	int	fd;

	fd = -1;
	if (msh_is_redirect(*cmd) == 1)
	{
		write(2, cmd->next->next->argv[0], ft_strlen(cmd->next->next->argv[0]));
		fd = open(cmd->next->next->argv[0], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (msh_is_redirect(*cmd) == 2)
	{
		write(2, cmd->next->next->argv[0], ft_strlen(cmd->next->next->argv[0]));
		fd = open(cmd->next->next->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	write(2, "fd: ", 4);
	write(2, ft_itoa(fd), ft_strlen(ft_itoa(fd)));
	write(2, "\n", 1);
	return (fd);
}