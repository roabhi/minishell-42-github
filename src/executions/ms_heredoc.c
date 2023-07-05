/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:41:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/05 17:34:00 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_close_pipes(int pobj[2])
{
	close(pobj[0]);
	close(pobj[1]);
}

void	msh_heredoc(char *delim, int hfd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, hfd[1]);
		free(line);
	}
	close(hfd[1]);
}
