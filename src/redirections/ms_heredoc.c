/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/29 19:16:25 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_store_heredoc2(t_cmd *cmd, int i)
{
	while (cmd != NULL && cmd->next != NULL)
	{
		if (msh_is_redirect_first(*cmd) == 4)
		{
			msh_heredoc(cmd->next->argv[0], ft_itoa(i));
			i++;
		}
		else if (msh_is_redirect(*cmd) == 4)
		{
			msh_heredoc(cmd->next->next->argv[0], ft_itoa(i));
			i++;
		}
		cmd = cmd->next->next;
	}
	return (i);
}

// i = 0; hdproc = NULL;
int	msh_store_heredocs(t_vars *vars, int i, pid_t hdproc)
{
	t_cmd	*cmd;

	cmd = vars->cmd;
	if (hdproc == 0)
	{
		msh_set_signals(3);
		i = msh_store_heredoc2(cmd, i);
		exit (g_return_status);
	}
	else
	{
		msh_set_signals(1);
		waitpid(hdproc, &g_return_status, 0);
	}
	msh_set_signals(2);
	g_return_status = WEXITSTATUS(g_return_status);
	return (i);
}

void	msh_heredoc(char *delim, char *fnum)
{
	char				*line;
	int					fd;
	char				*fname;

	fname = ft_joinloc(ft_strdup(".heredoc"), fnum);
	fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit (g_return_status);
		if ((ft_strcmp(line, delim) == 0) || msh_check_sigint(0))
		{
			free(line);
			exit (g_return_status);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	msh_check_sigint(-1);
	free(fname);
	close(fd);
}

char	*msh_read_heredoc(int hdnbr)
{
	char	*hdname;

	hdname = ft_joinloc(ft_strdup(".heredoc"), ft_itoa(hdnbr));
	while (hdnbr < 999)
	{
		if (access(hdname, F_OK) == 0)
			return (hdname);
		hdnbr++;
		free(hdname);
		hdname = ft_joinloc(ft_strdup(".heredoc"), ft_itoa(hdnbr));
	}
	free(hdname);
	return (NULL);
}
