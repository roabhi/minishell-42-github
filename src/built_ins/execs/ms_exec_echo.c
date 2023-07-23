/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:40:12 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/22 21:58:24 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_echo_print(t_cmd *cmd, int n_flags, int index)
{
	int	c;

	if (!cmd->argv[index])
	{
		if (!n_flags)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (index < cmd->argc)
	{
		c = 0;
		if (!cmd->argv[index])
			ft_putchar_fd(' ', 1);
		while (cmd->argv[index] && cmd->argv[index][c])
		{
			if (cmd->argv[index][c])
				ft_putchar_fd(cmd->argv[index][c], 1);
			c++;
		}
		if (cmd->argv[index + 1])
			ft_putchar_fd(' ', 1);
		if (index == cmd->argc - 1 && !n_flags)
			ft_putchar_fd('\n', 1);
		index++;
	}
}

int	msh_echo_has_n_flag(char *arg)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = 1;
	return (n_flag);
}

void	msh_exec_echo(t_cmd *cmd, t_vars *vars)
{
	int	index;
	int	n_flags;

	(void)vars;
	index = 0;
	n_flags = 0;
	if (cmd)
	{
		while (cmd->argv[++index] && msh_echo_has_n_flag(cmd->argv[index]))
			n_flags = 1;
	}
	msh_echo_print(cmd, n_flags, index);
	g_return_status = 0;
}
