/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:56:12 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/22 18:57:08 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

char	**msh_realloc_env_vars(t_vars *vars, int length)
{
	char	**new_env;
	int		c;

	new_env = ft_calloc(length + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	c = 0;
	while (vars->envar[c] && c < length)
	{
		new_env[c] = ft_strdup(vars->envar[c]);
		msh_free_ptr(vars->envar[c]);
		c++;
	}
	free(vars->envar);
	return (new_env);
}

int	msh_remove_envar(t_vars *vars, int index)
{
	int	c;
	int	j;

	if (index > msh_get_env_vars_length(vars))
		return (-1); // ? Index is off limits. something went wrong here
	// ? remove / free current envar and set it to NULL
	
	msh_free_ptr(vars->envar[index]);
	c = index;
	j = index;
	while (vars->envar[c + 1])
	{
		vars->envar[c] = ft_strdup(vars->envar[c + 1]);
		msh_free_ptr(vars->envar[c + 1]);
		j++;
		c++;
	}
	vars->envar = msh_realloc_env_vars(vars, j);
	if (!vars->envar)
		return (-1); // ? Failure in reallocating env vars
	return (0);
}


void	msh_exec_unset(t_cmd *cmd, t_vars *vars)
{
	int	c;
	int	env_index;

	c = 0;
	if (cmd->argc == 1)
		ft_putendl_fd("unset: Not enough arguments", 2);
	while (cmd->argv[++c])
	{		
		env_index = msh_get_env_index(vars, cmd->argv[c]);
		if (env_index != -1)
			msh_remove_envar(vars, env_index);
		// else
		// 	printf("No envar with that name\n"); // TODO this needs to get the var unable to unset via reference
	}


} // ? This function should return EXIT_SUCCESS or 0 ?