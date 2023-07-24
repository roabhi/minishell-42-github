/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validations_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:19:54 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/24 15:31:08 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_argv_need_expansion(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	return (0);
}

int	msh_chr_is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	msh_chr_is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	msh_chr_is_double_redirection(char c, char x)
{
	if ((c == '<' && x == '<') || (c == '>' && x == '>'))
		return (1);
	return (0);
}


