/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:41:30 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/28 21:37:19 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_print_element(char *input, int start, int end)
{
	printf("\nstart es %d y end es %d\n", start, end);

	while (start <= end)
	{
		write(1, &input[start], 1);
		start++;
	}
	printf("\n");
}

void	msh_print_env_vars(t_vars *vars, char *str)
{
	int		env_length;
	int		c;
	char	*substr;
	char	*env_value;

	env_length = -1;
	if (!str)
		str = "\0";
	while (vars->envar[++env_length])
	{
		if (!str)			
			printf("%s%s\n", str, vars->envar[env_length]);
		else
		{
			c = -1;
			substr = NULL;
			env_value = msh_get_env_value(vars, env_length);
			while (vars->envar[env_length][++c] != '=')
				substr = msh_strjoinchr(substr, vars->envar[env_length][c]);
			printf("%s%s=\"%s\"\n", str, substr, env_value);
			msh_free_ptr(substr);
			msh_free_ptr(env_value);
		}
	}
}

void	msh_debug_cmd_list(t_cmd *first)
{
	t_cmd	*cmd;
	int		count;

	count = -1;
	if (first)
	{
		while (first)
		{
			cmd = first;
			if (cmd->is_separator)
				printf("Este token ES un separador!\n ==================== \n");
			else
				printf("Este token NO ES un separador!\n ==================== \n");
			printf("El index de este comando es %d, el numero de argumentos es %d y son:\n",cmd->index, cmd->argc);
			while (cmd->argv[++count])
				printf("|%s|\n", cmd->argv[count]);
			count = -1;
			first = first->next;
		}
	}
}
