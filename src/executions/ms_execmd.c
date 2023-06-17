/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:21:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/17 19:07:41 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_execute_start(t_vars *vars)
{
	//aqui ha de ir todo el desglose para hacer pipes redirecciones y tonterias de multiples comandos

	//probando ejecucion de un comando simple
	write(1 , "enters cmd execute start\n", 26);
	msh_getpath(vars, vars->envar);
	write(1 , "exits getpath\n", 14);
	msh_cmd_execute(vars);
	msh_free_raw_array(vars->paths); // ? free tokens
	return (0); // aqui poner return de error o result cuando toque
}

int	msh_cmd_execute(t_vars *vars)
{
	pid_t	exec_pid;
	char	*temp_cmd;
	
	write(1 , "enters cmd execute\n", 19);
	temp_cmd = msh_getpath_cmd(vars, vars->cmd->argv[0]);
	if (temp_cmd == NULL)
		return (1);
	exec_pid = fork();
	if (exec_pid == 0)
	{
		if (temp_cmd != NULL && vars->cmd->argv[0])
		{
			printf("cmd: %s\n", temp_cmd);
			// vars->sigexec = 1;
			execve(temp_cmd, vars->cmd->argv, vars->envar);
		}
		// else
		// 	vars->sigexec = 0;
	}
	else
		waitpid(exec_pid, NULL, 0);
	free(temp_cmd);
	return (0);
}