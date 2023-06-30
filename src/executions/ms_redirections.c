/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/30 17:20:33 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_save_io(int save[2])
{
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
}

void	msh_restore_io(int save[2])
{
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	close(save[0]);
	close(save[1]);
}

//redirect 0 == break
//redirect 1 == read
//redirect 2 == write
//redirect 3 == append
//redirect 4 == heredoc
int	msh_is_redirect(t_cmd tcmd)
{
	if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], "<") == 0)
		return (1);
	else if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], ">") == 0)
		return (2);
	else if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], ">>") == 0)
		return (3);
	return (0);
}

//testing variable
void	msh_putfd_fd(int fd, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" fd: ", 2);
	ft_putnbr_fd(fd, 2);
	ft_putendl_fd("", 2);
}

void	msh_exec_redirect(t_cmd *cmd)
{
	int	fd;
	int	rdtype;

	fd = -1;
	rdtype = msh_is_redirect(*cmd);
	if (rdtype == 1)
	{
		fd = open(cmd->next->next->argv[0], O_RDONLY);
		msh_putfd_fd(fd, "input read");
		dup2(fd, STDIN_FILENO);
	}
	else if (rdtype == 2)
	{
		fd = open(cmd->next->next->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		msh_putfd_fd(fd, "output write");
		dup2(fd, STDOUT_FILENO);
	}
	else if (rdtype == 3)
	{
		fd = open(cmd->next->next->argv[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		msh_putfd_fd(fd, "output append");
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}