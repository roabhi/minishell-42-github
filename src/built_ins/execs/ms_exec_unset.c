/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:56:12 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/19 20:10:40 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_exec_unset(t_cmd *cmd, t_vars *vars)
{
	int	c;
	(void)vars;

	c = 0;
	printf("El numero de variables a borrar es\n");
	while (cmd->argv[++c])
		printf("%s\n", cmd->argv[c]);


} // ? This function should return EXIT_SUCCESS or 0 ?