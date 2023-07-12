/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:08:07 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/12 18:33:06 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_is_first_redirect(t_cmd tcmd)
{
	if (tcmd.is_separator == 1 && tcmd.next != NULL
		&& ft_strcmp(tcmd.argv[0], "<") == 0)
		return (1);
	else if (tcmd.is_separator == 1 && tcmd.next != NULL
		&& ft_strcmp(tcmd.argv[0], ">") == 0)
		return (2);
	else if (tcmd.is_separator == 1 && tcmd.next != NULL
		&& ft_strcmp(tcmd.argv[0],">>") == 0)
		return (3);
	else if (tcmd.is_separator == 1 && tcmd.next != NULL
		&& ft_strcmp(tcmd.argv[0], "<<") == 0)
		return (4);
	return (0);
}

void	msh_exec_first_redirect2(t_cmd *cmd, int fd, int hdnbr)
{
	char	*hdname;

	if (msh_is_first_redirect(*cmd) == 4)
	{
		hdname = msh_read_heredoc(hdnbr);
		fd = open(hdname, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		unlink(hdname);
		free(hdname);
	}
}

//fd must be always -1 on function input
int	msh_exec_first_redirect(t_cmd *cmd, int fd, char *argv, int hdnbr)
{
	if (msh_is_first_redirect(*cmd) == 1)
	{
		if (access(argv, F_OK) != 0)
		{
			msh_print_error(argv, ": No such file or directory\n");
			return (1);
		}
		fd = open(argv, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (msh_is_first_redirect(*cmd) == 2 || msh_is_first_redirect(*cmd) == 3)
	{
		if (msh_is_first_redirect(*cmd) == 2)
			fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (msh_is_first_redirect(*cmd) == 3)
			fd = open(argv, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	msh_exec_first_redirect2(cmd, fd, hdnbr);
	close(fd);
	return (0);
}