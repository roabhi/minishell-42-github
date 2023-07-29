/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:41:03 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/29 19:50:35 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_errors_syntax_extra(int flag, char *param)
{
	if (!param)
		param = "";
	if (flag == 0)
		return (0);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("'\n", 2);
	g_return_status = 258;
	return (1);
}

//set flag always at 0
int	msh_errors_syntax(t_cmd *cmd, char *param, int flag)
{
	if (cmd->argv[0][0] == '|')
		flag = 1;
	param = cmd->argv[0];
	while (cmd->next && flag == 0)
	{
		if (cmd->is_separator == 1 && cmd->next->is_separator == 1)
		{
			if (cmd->argv[0][0] != '|' && (cmd->next->argv[0][0] != '<'
				|| cmd->next->argv[0][0] != '>' ))
			{
				flag = 1;
				param = cmd->next->argv[0];
				break ;
			}
		}
		cmd = cmd->next;
	}
	if (cmd->is_separator == 1 && cmd->next == NULL)
	{
		flag = 1;
		param = "newline";
	}
	return (msh_errors_syntax_extra(flag, param));
}
