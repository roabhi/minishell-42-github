/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/12 17:25:54 by eros-gir         ###   ########.fr       */
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
	else if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], "<<") == 0)
		return (4);
	return (0);
}

int	msh_set_redirect(t_vars *vars, t_cmd *tcmd)
{
	if (msh_is_redirect(*vars->cmd))
	{
		while (tcmd->next != NULL)
		{
			if (msh_exec_redirect(tcmd, -1, tcmd->next->next->argv[0], 0))
				return (1);
			tcmd = tcmd->next->next;
		}
	}
	return (0);
}

void msh_exec_redirect2(t_cmd *cmd, int fd, char *argv, int hdnbr)
{
	char	*hdname;

	if (msh_is_redirect(*cmd) == 4)
	{
		hdname = msh_read_heredoc(hdnbr);
		fd = open(hdname, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		unlink(hdname);
		free(hdname);
	}
}

//fd must be always -1 on function input
int	msh_exec_redirect(t_cmd *cmd, int fd, char *argv, int hdnbr)
{
	if (msh_is_redirect(*cmd) == 1)
	{
		if (access(argv, F_OK) != 0)
		{
			msh_print_error(argv, ": No such file or directory\n");
			return (1);
		}
		fd = open(argv, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (msh_is_redirect(*cmd) == 2 || msh_is_redirect(*cmd) == 3)
	{
		if (msh_is_redirect(*cmd) == 2)
			fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (msh_is_redirect(*cmd) == 3)
			fd = open(argv, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	msh_exec_redirect2(cmd, fd, argv, hdnbr);
	close(fd);
	return (0);
}
