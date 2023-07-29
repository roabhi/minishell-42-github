/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:13:45 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/29 18:57:35 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

//redirect 0 == break
//redirect 1 == read
//redirect 2 == write
//redirect 3 == append
//redirect 4 == heredoc
int	msh_is_redirect_first(t_cmd tcmd)
{
	if (tcmd.next != NULL && tcmd.is_separator == 1
		&& ft_strcmp(tcmd.argv[0], "<") == 0)
		return (1);
	else if (tcmd.next != NULL && tcmd.is_separator == 1
		&& ft_strcmp(tcmd.argv[0], ">") == 0)
		return (2);
	else if (tcmd.next != NULL && tcmd.is_separator == 1
		&& ft_strcmp(tcmd.argv[0], ">>") == 0)
		return (3);
	else if (tcmd.next != NULL && tcmd.is_separator == 1
		&& ft_strcmp(tcmd.argv[0], "<<") == 0)
		return (4);
	return (0);
}

int	msh_set_redirect_first(t_vars *vars, t_cmd *tcmd)
{
	if (msh_is_redirect_first(*vars->cmd))
	{
		while (tcmd->next != NULL)
		{
			if (msh_exec_redirect_first(tcmd, -1, tcmd->next->argv[0], 0))
				return (g_return_status);
			tcmd = tcmd->next;
		}
	}
	return (g_return_status);
}

void	msh_exec_redirect2_first(t_cmd *cmd, int fd, int hdnbr)
{
	char	*hdname;

	if (msh_is_redirect_first(*cmd) == 4)
	{
		hdname = msh_read_heredoc(hdnbr);
		fd = open(hdname, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		unlink(hdname);
		free(hdname);
	}
}

//fd must be always -1 on function input
int	msh_exec_redirect_first(t_cmd *cmd, int fd, char *argv, int hdnbr)
{
	if (msh_is_redirect_first(*cmd) == 1)
	{
		if (access(argv, F_OK) != 0)
		{
			msh_print_error(argv, ": No such file or directory\n");
			return (1);
		}
		fd = open(argv, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (msh_is_redirect_first(*cmd) == 2
		|| msh_is_redirect_first(*cmd) == 3)
	{
		if (msh_is_redirect_first(*cmd) == 2)
			fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (msh_is_redirect_first(*cmd) == 3)
			fd = open(argv, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	msh_exec_redirect2_first(cmd, fd, hdnbr);
	close(fd);
	return (0);
}

char	*msh_set_final_cmd(char **tcmds, char *cmd)
{
	int		i;

	free (cmd);
	cmd = ft_strdup("");
	i = 0;
	while (tcmds[i] != NULL)
	{
		cmd = ft_joinloc(cmd, tcmds[i]);
		if (tcmds[i + 1] != NULL)
			cmd = ft_joinloc(cmd, ft_strdup(" "));
		i++;
	}
	free (tcmds);
	return (cmd);
}
