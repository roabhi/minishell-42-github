/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:21:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/27 17:45:21 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

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
	if (pipe(pobj) < 0)
		return (1); //pipe error
	child1 = fork();
	if (child1 < 0)
		return (1); //fork error
	else if (child1 == 0)
	{
		if (recursion)
		{
		//	write(2, "Middle pipe\n", 11);
			close(prev_pobj[1]);
			dup2(prev_pobj[0], STDIN_FILENO);
			close(prev_pobj[0]);
		}
		close(pobj[0]);
		dup2(pobj[1], STDOUT_FILENO);
		close(pobj[1]);

		while (!msh_is_pipe(tcmd2) && tcmd2.next != NULL)
		{
			msh_exec_redirect(&tcmd2);
			tcmd2 = *tcmd2.next->next;
		}
		//	write(2, "First pipe\n", 10);
		if(msh_cmd_is_built_in(&tcmd))
			msh_exec_builtin(&tcmd, vars);
		else
		{
			msh_getpath(vars, vars->envar);
			msh_cmd_execute(vars, &tcmd);
			msh_free_raw_array(vars->paths); // ? free paths
		}
		exit (0);
	}
	if (recursion != 0)
	{
		close(prev_pobj[0]);
		close(prev_pobj[1]);
	}
	tcmd = *tcmd.next->next;
	if (msh_is_pipe(tcmd))
		msh_pipe_fork(vars, &tcmd, pobj, 1);
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (1); //fork error
		else if (child2 == 0)
		{
		//	write(2, "Last pipe\n", 10);
			close(pobj[1]);
			dup2(pobj[0], STDIN_FILENO);

			while (!msh_is_pipe(tcmd2) && tcmd2.next != NULL)
			{
				msh_exec_redirect(&tcmd2);
				tcmd2 = *tcmd2.next->next;
			}
			if (msh_cmd_is_built_in(&tcmd))
				msh_exec_builtin(&tcmd, vars);
			else
			{
				msh_getpath(vars, vars->envar);
				msh_cmd_execute(vars, &tcmd);
				msh_free_raw_array(vars->paths); // ? free paths
			}
			exit (0);
		}
	}	
	close(pobj[0]);
	close(pobj[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}

int	msh_execute_start(t_vars *vars)
{
	pid_t	single;
	int		pobj[2];
	t_cmd	*tcmd;
	//aqui ha de ir todo el desglose para hacer pipes redirecciones y tonterias de multiples comandos
	pobj[0] = 0;
	pobj[1] = 0;
	tcmd = vars->cmd;
	if (msh_is_pipe(*vars->cmd))
		msh_pipe_fork(vars, vars->cmd, pobj, 0);
	else
	{
	//probando ejecucion de un comando simple
		if (msh_is_redirect(*vars->cmd))
		{
			while (!msh_is_pipe(*tcmd) && tcmd->next != NULL)
			{
				msh_exec_redirect(tcmd);
				tcmd = tcmd->next->next;
			}
		}
		if (msh_cmd_is_built_in(vars->cmd))
		{
			//write(2, "Built-in\n", 9);
			msh_exec_builtin(vars->cmd, vars);
		}
		else
		{
			single = fork();
			if (single < 0)
				return (1); //fork error
			else if (single == 0)
			{
				msh_getpath(vars, vars->envar);
				msh_cmd_execute(vars, vars->cmd);
				msh_free_raw_array(vars->paths); // ? free paths
				exit (0);
			}
			else
				waitpid(single, NULL, 0);
		}
	}
	return (0); // aqui poner return de error o result cuando toque
}

int	msh_cmd_execute(t_vars *vars, t_cmd *cmd)
{
	char	*temp_cmd;

	temp_cmd = msh_getpath_cmd(vars, cmd->argv[0]);
	g_return_status = 0;
	if (temp_cmd == NULL)
		return (1);
	if (temp_cmd != NULL && cmd->argv[0])
	{
		//printf("cmd: %s\n", temp_cmd);
		g_return_status = execve(temp_cmd, cmd->argv, vars->envar);
	}
	free(temp_cmd);
	return (0);
}