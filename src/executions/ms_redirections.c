/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/28 18:07:42 by eros-gir         ###   ########.fr       */
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
}

int	msh_is_redirect(t_cmd tcmd)
{
	if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], "<") == 0)
	{
	//	write(2, "Redirect Input\n", 15);
		return (1);
	}
	else if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], ">") == 0)
	{
	//	write(2, "Redirect Output\n", 17);
		return (2);
	}
	return (0);
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
		dup2(fd, STDIN_FILENO);
	}
	else if (rdtype == 2)
	{
		fd = open(cmd->next->next->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}