/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:41:03 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/24 19:35:42 by eros-gir         ###   ########.fr       */
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
