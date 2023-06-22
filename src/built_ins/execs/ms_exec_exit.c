/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:16:13 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/21 22:32:01 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

// function que determina si el argumento es valido. Ha de ser un numero
// Si es un numero saldremos con el valor de ese numero
// Si no es un numero, saldremos con 255


void	msh_exec_exit(t_cmd *cmd, t_vars *vars)
{

	(void)vars;
	vars->looping = 0;

	if(cmd->argc == 1)
	{
		g_return_status = 1;
	}
	if (cmd->argc == 2)
	{
		printf("%s", cmd->argv[1]);
		//validar numero, si no es bueno salir con 255
		// si es valido con el atoi de ese numero
		g_return_status = 1;
	}
	else{
		printf("Exit tiene mas de 2 argumentos\n");
		g_return_status = 255;
	}
}
