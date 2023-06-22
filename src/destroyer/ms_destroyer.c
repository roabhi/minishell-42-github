/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_destroyer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:11:39 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/20 16:12:06 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_free_envars(t_vars *vars)
{
	int	env_length;

	env_length = 0;
	while (vars->envar[env_length])
	{
		//free(vars->envar[env_length]);
		//printf("\n%d - %s",env_length, vars->envar[env_length]);
		free(vars->envar[env_length]);
		env_length++;
	}
	free(vars->envar);
}

// ? Avoid double free when possible
void	msh_free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*msh_free_return_null(char *ptr)
{
	free(ptr);
	return (NULL);
}

void	msh_free_cmd_list(t_cmd *first)
{
	t_cmd	*cmd;
	int		count;
	void	*aux;

	count = -1;
	if (first)
	{
		while (first)
		{
			cmd = first;
			aux = cmd->next;
			first = aux;
			while (cmd->argv[++count])
				free(cmd->argv[count]);
			count = -1;
			free(cmd->argv);
			free(cmd);
		}
		first = NULL;
	}
}

void	msh_free_raw_array(char **arr)
{
	int	c;

	c = -1;
	while (arr[++c])
	{
		// printf("El token es %s", vars.tokens[c]);
		free(arr[c]);
	}
	free(arr);
}
