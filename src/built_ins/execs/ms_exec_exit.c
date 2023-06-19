/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:16:13 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/19 18:23:58 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_exec_exit(t_cmd *cmd, t_vars *vars)
{
	(void)cmd;
	vars->looping = 0;
	g_return_status = 1;
}
