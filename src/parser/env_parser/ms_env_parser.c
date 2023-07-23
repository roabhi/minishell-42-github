/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:52:50 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/22 20:08:42 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

int	msh_store_env_own_lines(t_vars *vars, char **envp, int index)
{
	int		env_line_length;

	env_line_length = 0;
	while (envp[index][env_line_length])
		env_line_length++;
	vars->envar[index] = (char *)malloc(sizeof(char)
			* env_line_length + 1);
	if (!vars->envar[index])
		return (0);
	env_line_length = -1;
	while (envp[index][++env_line_length])
	{
		vars->envar[index][env_line_length]
			= envp[index][env_line_length];
	}
	vars->envar[index][env_line_length] = '\0';
	return (1);
}

int	msh_store_env_own_vars(t_vars *vars, char **envp)
{
	int		env_length;

	env_length = 0;
	while (envp[env_length])
		env_length++;
	vars->envar = (char **)malloc(sizeof(char *) * env_length + 1);
	if (!vars->envar)
		return (0);
	vars->envar[env_length] = NULL;
	env_length = 0;
	while (envp[env_length])
	{
		if (!msh_store_env_own_lines(vars, envp, env_length))
			return (0);
		env_length++;
	}
	return (1);
}
