/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:41:03 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/09 20:33:10 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"
// ? I need to print for sure "minishell: "
// ? Then the command is executing the print. Can be exit / cd / whatever
// ?

void	msh_errors_exit(char *param, char *msg)
{
	if (!param)
		param = "";
	write(2, "minishell: exit: ", 17);
	write(2, param, ft_strlen(param));
	write(2, msg, ft_strlen(msg));
}

void	msh_errors_export(char *param, char *msg)
{
	if (!param)
		param = "";
	write(2, "minishell: export: `", 20);
	write(2, param, ft_strlen(param));
	write(2, msg, ft_strlen(msg));
}

int	msh_check_syntax(char *param)
{
	if (ft_strcmp(param, "<") == 0 || ft_strcmp(param, ">") == 0
		|| ft_strcmp(param, ">>") == 0 || ft_strcmp(param, "<<") == 0)
		return (1);
	return (0);
}

int	msh_errors_syntax(t_cmd *cmd, char *param, int flag)
{
	while (cmd->next)
	{
		if (cmd->is_separator == 1 && cmd->next->is_separator == 1)
		{
			flag ++;
			if (flag > 2 && ft_strcmp(param, "|") == 0)
				break ;
			param = cmd->next->argv[0];
		}
		cmd = cmd->next;
	}
	// printf("flag: %d\n", flag);
	// printf("param: %s\n", param);
	if (flag == 0)
		return (0);
	if (!param)
		param = "";
	else if (msh_check_syntax(param) != 0 || param[0] == '\0'
		|| param[0] == '\n')
		param = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("'\n", 2);
	g_return_status = 258;
	return (1);
}