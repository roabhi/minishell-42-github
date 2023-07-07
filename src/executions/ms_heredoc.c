/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/07 18:13:58 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_close_pipes(int pobj[2])
{
	close(pobj[0]);
	close(pobj[1]);
}

int	msh_store_heredocs(t_vars *vars)
{
	t_cmd	*cmd;
	int		i;

	i = 20;
	cmd = vars->cmd;
	while (cmd != NULL && cmd->next != NULL)
	{
		if (msh_is_redirect(*cmd) == 4)
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
	char	*line;
	int		fd;
	char	*fname;

	fname = ft_joinloc(ft_strdup(".heredoc"), fnum);
	fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(fname);
	close(fd);
}
