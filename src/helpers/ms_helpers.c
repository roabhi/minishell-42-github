/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:41:30 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/15 20:54:37 by rabril-h         ###   ########.fr       */
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
