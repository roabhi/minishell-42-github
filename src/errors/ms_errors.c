/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:41:03 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/05 21:43:00 by rabril-h         ###   ########.fr       */
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

