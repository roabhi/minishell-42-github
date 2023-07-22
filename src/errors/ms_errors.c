/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:41:03 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/22 18:38:53 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_print_error(char *param, char *msg)
{
	if (!param)
		param = "";
	write(2, "minishell: ", 11);
	write(2, param, ft_strlen(param));
	write(2, msg, ft_strlen(msg));
}

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

int	msh_errors_syntax(t_cmd *cmd, char *param)
{
	int	flag;

	flag = 0;
	while (cmd->next)
	{
		if (cmd->is_separator == 1 && cmd->next->is_separator == 1)
		{
			flag = 1;
			param = cmd->next->argv[0];
			break ;
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
