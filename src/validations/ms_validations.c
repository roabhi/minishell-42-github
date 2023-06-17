/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:19:27 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/11 15:18:30 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_chr_can_be_separator(char c)
{
	if (c == '<' || c == '|' || c == '>')
		return (1);
	return (0);
}

int	msh_is_startarg(char *input, int c, t_quotes *quotes)
{
	if (c > 0 && input[c] != ' ' && input[c - 1] == ' '
		&& msh_no_quotes(quotes))
		return (1);
	return (0);
}

int	msh_is_endarg(char *input, int c, t_quotes *quotes)
{
	if (input[c] != ' ' && ((input[c + 1] == ' '
				&& msh_no_quotes(quotes)) || input[c + 1] == '\0' ))
		return (1);
	return (0);
}

int	msh_no_quotes(t_quotes *quotes)
{
	if (!quotes->quote && !quotes->miniquote)
		return (1);
	return (0);
}
