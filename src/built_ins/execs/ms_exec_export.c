/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:11:18 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/19 21:00:43 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_exec_export(t_cmd *cmd, t_vars *vars)
{
	int	c;

	c = 0;
	if (cmd->argc == 1)
		msh_print_env_vars(vars, "export ");
	else
	{
		while (cmd->argv[++c])
		{
			if (!is_valid_env_var_key(cmd->argv[c]))
				ft_putendl_fd("export: Not a valid identifer",2); // TODO make this dynamic through a unifed error system prompter
			else if (ft_strchr(cmd->argv[c], '=') != NULL)
			{
				printf("La variable a insertar es %s\n", cmd->argv[c]);
			}

		}
	}
	g_return_status = 1; // ! SUCCESS SO FAR
}
