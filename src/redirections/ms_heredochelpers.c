/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredochelpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/29 19:17:52 by eros-gir         ###   ########.fr       */
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

	i = -1;
	while (i <= 999)
	{
		fname = ft_joinloc(ft_strdup(".heredoc"), ft_itoa(i));
		unlink(fname);
		free(fname);
		i++;
	}
	vars->hdnumb = 0;
}

int	msh_check_sigint(int signum)
{
	static int	interrupt = 0;

	if (signum == 1)
	{
		interrupt = 1;
		rl_redisplay();
		write(1, "     ", 5);
		ioctl(0, TIOCSTI, "\n");
		g_return_status = 1;
		interrupt = 1;
	}
	else if (signum == -1)
		interrupt = 0;
	return (interrupt);
}

void	msh_sigint_heredoc(int signum)
{
	(void)signum;
	msh_check_sigint(1);
}
