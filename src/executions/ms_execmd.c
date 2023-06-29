/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:21:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/29 19:51:26 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_signal_return(int status)
{
	g_return_status = status;
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

int	msh_pipe_fork(t_vars *vars, t_cmd *cmd, int prev_pobj[2], int recursion)
{
	pid_t	child1;
	pid_t	child2;
	t_cmd	tcmd;
	t_cmd	tcmd2;
	int		pobj[2];

	tcmd = *cmd;
	tcmd2 = *cmd;
	child1 = -1;
	child2 = -1;
	//testing recursion return
	printf("recursion: %d\n", recursion);
	printf("cmd: %s\n", cmd->argv[0]);
	//end testing
	if (pipe(pobj) < 0)
		return (1); //pipe error
	child1 = fork();
	if (child1 < 0)
		return (1); //fork error
	else if (child1 == 0)
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
		if (msh_is_redirect(*vars->cmd))
		{
			while (!msh_next_pipe(tcmd2) && tcmd2.next != NULL)
			{
				msh_exec_redirect(&tcmd2);
				tcmd2 = *tcmd2.next->next;
			}
		}
		if (msh_cmd_is_built_in(&tcmd))
			msh_exec_builtin(&tcmd, vars);
		else
		{
			msh_getpath(vars, vars->envar);
			g_return_status = msh_cmd_execute(vars, &tcmd);
			msh_free_raw_array(vars->paths); // ? free paths
		}
		exit (g_return_status);
	}
	if (recursion != 0)
	{
		close(prev_pobj[0]);
		close(prev_pobj[1]);
	}
	while (msh_is_redirect(tcmd) && tcmd.next != NULL)
		tcmd = *tcmd.next->next;
	tcmd = *tcmd.next->next;
	tcmd2 = tcmd;
	if (msh_is_pipe(tcmd))
		msh_pipe_fork(vars, &tcmd, pobj, recursion + 1);
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (1); //fork error
		else if (child2 == 0)
		{
			close(pobj[1]);
			dup2(pobj[0], STDIN_FILENO);
			if (msh_is_redirect(*vars->cmd))
			{
				while (!msh_next_pipe(tcmd2) && tcmd2.next != NULL)
				{
					msh_exec_redirect(&tcmd2);
					tcmd2 = *tcmd2.next->next;
				}
			}
			if (msh_cmd_is_built_in(&tcmd))
				msh_exec_builtin(&tcmd, vars);
			else
			{
				msh_getpath(vars, vars->envar);
				g_return_status = msh_cmd_execute(vars, &tcmd);
				msh_free_raw_array(vars->paths); // ? free paths
			}
			exit (g_return_status);
		}
	}	
	close(pobj[0]);
	close(pobj[1]);
	waitpid(child1, &g_return_status, 0);
	waitpid(child2, &g_return_status, 0);
//	while (wait(NULL) > 0)
//		;
	return (0);
}

int	msh_execute_start(t_vars *vars)
{
	pid_t	single;
	int		pobj[2];
	t_cmd	*tcmd;
//	int		status;

	pobj[0] = 0;
	pobj[1] = 0;
	tcmd = vars->cmd;
	msh_save_io(vars->iofd);
	g_return_status = 0;
//	status = 0;
	if (msh_is_pipe(*tcmd))
		msh_pipe_fork(vars, vars->cmd, pobj, 0);
	else
	{
		if (msh_is_redirect(*vars->cmd))
		{
			while (tcmd->next != NULL)
			{
				msh_exec_redirect(tcmd);
				tcmd = tcmd->next->next;
			}
		}
		if (msh_cmd_is_built_in(vars->cmd))
			msh_exec_builtin(vars->cmd, vars);
		else
		{
			single = fork();
			if (single < 0)
				return (1); //fork error
			else if (single == 0)
			{
				msh_getpath(vars, vars->envar);
				g_return_status = msh_cmd_execute(vars, vars->cmd);
				msh_free_raw_array(vars->paths); // ? free paths
				exit(g_return_status);
			}
			waitpid(single, &g_return_status, 0);
		}
	}
	msh_restore_io(vars->iofd);
	g_return_status = WEXITSTATUS(g_return_status);
	printf("return status: %d\n", g_return_status);
	return (0); // aqui poner return de error o result cuando toque
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
	{
		//printf("cmd: %s\n", temp_cmd);
		rtn = execve(temp_cmd, cmd->argv, vars->envar);
	}
	free(temp_cmd);
	return (rtn);
}