/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredochelpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/22 16:04:27 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_close_pipes(int pobj[2])
{
	close(pobj[0]);
	close(pobj[1]);
}

void	msh_clean_heredoc(t_vars *vars)
{
	char	*fname;
	int		i;

	i = 0;
	while (i >= 999)
	{
		fname = ft_joinloc(ft_strdup(".heredoc"), ft_itoa(i));
		unlink(fname);
		free(fname);
		i++;
	}
	vars->hdnumb = 0;
}
