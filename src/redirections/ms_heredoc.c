/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/19 20:24:10 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_close_pipes(int pobj[2])
{
	close(pobj[0]);
	close(pobj[1]);
}

void	msh_clean_heredoc(t_vars *vars)
{
	char	*fname;
	int		i;

	i = 0;
	while (i >= 999)
	{
		fname = ft_joinloc(ft_strdup(".heredoc"), ft_itoa(i));
		unlink(fname);
		free(fname);
		i++;
	}
	vars->hdnumb = 0;
}

int	msh_store_heredocs(t_vars *vars)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = vars->cmd;
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
		if (line == NULL) //necesito una forma de contolar ctrl+c
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
//	signal(SIGINT, SIG_IGN);
//	signal(SIGINT, msh_sigint_handler);
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