/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:21:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/07 18:26:01 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_pipe_fork1(t_vars *vars, t_cmd *cmd, int prev_pobj[2], int rc)
{
	pid_t	child1;
	pid_t	child2;
	t_cmd	tcmd;
	t_cmd	tcmd2;
	int		pobj[2];

	tcmd = *cmd;
	tcmd2 = *cmd;
	child2 = -1;
	if (pipe(pobj) < 0)
		return (1);
	child1 = fork();
	if (child1 < 0)
		return (1);
	else if (child1 == 0)
	{
		msh_pipe_child1(pobj, prev_pobj, rc);
		msh_pipe_execute(vars, &tcmd2, &tcmd);
	}
	if (rc != 0)
		msh_close_pipes(prev_pobj);
	g_return_status = msh_pipe_fork2(vars, tcmd, pobj, child2);
	while (wait(NULL) > 0)
		;
	return (0);
}

int	msh_pipe_fork2(t_vars *vars, t_cmd tcmd, int pobj[2], pid_t child2)
{
	t_cmd	tcmd2;

	while (msh_is_redirect(tcmd) && tcmd.next != NULL)
		tcmd = *tcmd.next->next;
	tcmd = *tcmd.next->next;
	tcmd2 = tcmd;
	if (msh_is_pipe(tcmd))
		msh_pipe_fork1(vars, &tcmd, pobj, 1);
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (1);
		else if (child2 == 0)
		{
			msh_pipe_child2(pobj);
			msh_pipe_execute(vars, &tcmd2, &tcmd);
		}
	}
	msh_close_pipes(pobj);
	waitpid(child2, &g_return_status, 0);
	return (g_return_status);
}

int	msh_execute_start(t_vars *vars)
{
	pid_t	single;
	int		pobj[2];
	t_cmd	*tcmd;

	pobj[0] = 0;
	pobj[1] = 0;
	tcmd = vars->cmd;
	vars->hdnumb = msh_store_heredocs(vars);
	single = fork();
	if (single < 0)
		return (1);
	g_return_status = 0;
	msh_save_io(vars->iofd);
	if (msh_is_pipe(*tcmd))
	{
		kill (single, SIGKILL);
		msh_pipe_fork1(vars, vars->cmd, pobj, 0);
		g_return_status = WEXITSTATUS(g_return_status);
	}
	else
		msh_single_cmd(vars, single, tcmd);
	msh_restore_io(vars->iofd);
	return (g_return_status);
}
// para ver el status de salida de un comando
//antes de return(); en la funcion anterior poner:
//	printf("g_return_status: %d\n", g_return_status);

void	msh_single_cmd(t_vars *vars, pid_t single, t_cmd *tcmd)
{
	if (msh_cmd_is_built_in(vars->cmd))
	{
		kill (single, SIGKILL);
		if (msh_is_redirect(*vars->cmd))
		{
			while (tcmd->next != NULL)
			{
				msh_exec_redirect(tcmd, -1, tcmd->next->next->argv[0], 20);
				tcmd = tcmd->next->next;
			}
		}
		msh_exec_builtin(vars->cmd, vars);
	}
	else
	{
		if (single == 0)
		{
			if (msh_is_redirect(*vars->cmd))
			{
				while (tcmd->next != NULL)
				{
					msh_exec_redirect(tcmd, -1, tcmd->next->next->argv[0], 20);
					tcmd = tcmd->next->next;
				}
			}
			msh_getpath(vars, vars->envar);
			g_return_status = msh_cmd_execute(vars, vars->cmd);
			msh_free_raw_array(vars->paths);
			exit(g_return_status);
		}
		waitpid(single, &g_return_status, 0);
		g_return_status = WEXITSTATUS(g_return_status);
	}
}

int	msh_cmd_execute(t_vars *vars, t_cmd *cmd)
{
	char	*temp_cmd;
	int		rtn;

	rtn = 0;
	temp_cmd = msh_getpath_cmd(vars, cmd->argv[0]);
	if (temp_cmd == NULL)
		return (127);
	if (cmd->argv[0])
		rtn = execve(temp_cmd, cmd->argv, vars->envar);
	free(temp_cmd);
	return (rtn);
}
