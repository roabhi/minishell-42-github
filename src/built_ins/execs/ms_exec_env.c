/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:21:04 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/18 20:08:40 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_exec_env(t_cmd *cmd, t_vars *vars)
{
	int	env_length;

	env_length = -1;
	if (cmd->argv && cmd->argv[1])
		// ? This should return shomething
		ft_putendl_fd("env: Too many arguments for minishell", 2);
	else
	{
		while (vars->envar[++env_length])
			ft_putendl_fd(vars->envar[env_length], 1);
	}
} // ? This function should return EXIT_SUCCESS or 0 ?

// * STDOUT_FILENO = 1