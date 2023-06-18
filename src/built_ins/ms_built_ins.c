/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:14:08 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/18 18:46:56 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_exec_builtin(t_cmd *cmd, t_vars *vars)
{
	(void)vars;

	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		msh_exec_echo(cmd, vars);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		printf("exec cd\n");
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		msh_exec_pwd(cmd, vars);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		printf("exec export\n");
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		printf("exec unset\n");
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		msh_exec_env(cmd, vars);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		msh_exec_exit(cmd, vars);
}

/**
 * @brief Functions that determines if string is a built in
 * 
 * @param str * 
 */


int	msh_cmd_is_built_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}
