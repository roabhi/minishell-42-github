/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:48:06 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 16:11:23 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

// 0 = default, 1 = ignore all, 2 = block cmds, 3 = heredoc
void	msh_set_signals(int type)
{
	if (type == 0)
	{
		signal(SIGINT, msh_sigint_handler);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == 2)
	{
		signal(SIGINT, msh_sigint_handler_block_cmds);
		signal(SIGQUIT, msh_sigquit_handler);
	}
	else if (type == 3)
	{
		signal(SIGINT, msh_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	msh_sigint_handler(int sig)
{
	if (sig != 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "                              \n", 31);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_return_status = 1;
	}
}

void	msh_sigint_handler_block_cmds(int sig)
{
	if (sig != 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_return_status = 130;
	}
}

void	msh_sigquit_handler(int sig)
{
	if (sig != 0)
	{
		printf("Quit: %d\n", sig);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_return_status = 131;
	}
}

void	msh_ignore_signals(t_vars *vars, int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac > 1 || av[1] != NULL)
	{
		ft_putendl_fd("ERROR: the program does not take any arguments!", 2);
		exit(1);
	}
	vars->sigbool = 1;
	vars->looping = 1;
	msh_set_signals(0);
}
