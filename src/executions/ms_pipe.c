/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:18:48 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/05 17:42:02 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_pipe_child1(int pobj[2], int prev_pobj[2], int recursion)
{
	if (recursion)
	{
		close(prev_pobj[1]);
		dup2(prev_pobj[0], STDIN_FILENO);
		close(prev_pobj[0]);
	}
	close(pobj[0]);
	dup2(pobj[1], STDOUT_FILENO);
	close(pobj[1]);
}

void	msh_pipe_child2(int pobj[2])
{
	close(pobj[1]);
	dup2(pobj[0], STDIN_FILENO);
	close(pobj[0]);
}

void	msh_pipe_execute(t_vars *vars, t_cmd *tcmd2, t_cmd *tcmd)
{
	while (msh_is_redirect(*tcmd2))
	{
		msh_exec_redirect(tcmd2, -1, tcmd2->next->next->argv[0]);
		tcmd2 = tcmd2->next->next;
	}
	if (msh_cmd_is_built_in(tcmd))
		msh_exec_builtin(tcmd, vars);
	else
	{
		msh_getpath(vars, vars->envar);
		g_return_status = msh_cmd_execute(vars, tcmd);
		msh_free_raw_array(vars->paths);
	}
	exit (g_return_status);
}

int	msh_next_pipe(t_cmd tcmd)
{
	if (tcmd.next != NULL && tcmd.next->is_separator == 1
		&& tcmd.next->next != NULL
		&& ft_strcmp(tcmd.next->argv[0], "|") == 0)
		return (1);
	return (0);
}

int	msh_is_pipe(t_cmd tcmd)
{
	while (tcmd.next != NULL)
	{
		if (tcmd.next != NULL && tcmd.next->is_separator == 1
			&& tcmd.next->next != NULL
			&& ft_strcmp(tcmd.next->argv[0], "|") == 0)
			return (1);
		tcmd = *tcmd.next;
	}
	return (0);
}
