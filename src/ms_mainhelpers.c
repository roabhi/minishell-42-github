/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mainhelpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:55:30 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 17:00:59 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

void	msh_free_memory_dynamic(t_vars *vars, int flag)
{
	if (flag == 0)
	{
		msh_free_cmd_list(vars->cmd);
		msh_free_raw_array(vars->tokens);
		free(vars->input);
	}
	else if (flag == 1)
	{
		msh_clean_heredoc(vars);
		msh_free_cmd_list(vars->cmd);
		msh_free_raw_array(vars->tokens);
		free(vars->input);
	}
	else if (flag == 2)
		free(vars->inpli);
	else if (flag == 3)
	{
		msh_free_envars(vars);
		free(vars->prompt);
	}
	else if (flag == 4)
	{
		msh_free_cmd_list(vars->cmd);
		msh_free_raw_array(vars->tokens);
	}
}

void	msh_reorder_input(t_vars *vars)
{
	msh_free_memory_dynamic(vars, 4);
	vars->input = msh_add_space_between_input(vars->input, 0, -1, -1);
	msh_reorder_redirs(vars);
	vars->cmd = msh_tokenize(vars);
}

void	msh_execute_main2(t_vars *vars)
{
	msh_expander(vars);
	msh_execute_start(vars);
}

void	msh_execute_main(t_vars *vars)
{
	msh_reorder_input(vars);
	if (vars->cmd != NULL)
		msh_execute_main2(vars);
	msh_free_memory_dynamic(vars, 1);
}

int	msh_check_errors_syntax(t_vars *vars)
{
	if (msh_errors_syntax(vars->cmd, NULL, 0))
	{
		msh_free_memory_dynamic(vars, 0);
		return (0);
	}
	return (1);
}
