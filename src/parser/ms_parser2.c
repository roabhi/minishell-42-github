/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:07:56 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/26 21:21:43 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_cs(char *input, int qf, int i, int count)
{
	while (input[++i] != '\0')
	{
		qf = msh_quote_flag(input[i], qf);
		if (qf == 1 || qf == 2)
			continue ;
		if (((input[i] == '>' && input[i + 1] != '>')
				|| (input[i] == '<' && input[i + 1] != '<'))
			&& input[i + 1] != ' ')
			count ++;
		else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
		{
			i ++;
			count ++;
		}
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] != ' ')
		{
			i ++;
			count ++;
		}
		else if ((input[i] != ' ' || input[i] != '>' || input[i] != '<')
			&& (input[i + 1] == '>' || input[i + 1] == '<'))
			count ++;
	}
	return (count);
}

int	msh_checktype_input(char *input, int i)
{
	if (((input[i] == '>' && input[i + 1] != '>')
			|| (input[i] == '<' && input[i + 1] != '<'))
		&& input[i + 1] != ' ')
		return (1);
	else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
		return (2);
	else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] != ' ')
		return (3);
	else if ((input[i] != ' ' || input[i] != '>' || input[i] != '<')
		&& (input[i + 1] == '>' || input[i + 1] == '<') 
		&& input[i + 2] != ' ')
		return (4);
	return (0);
}

// put always qf = 0, int i = -1, int j = -1;
char	*msh_add_space_between_input(char *in, int qf, int i, int j)
{
	char	*result;

	result = ft_calloc(sizeof(char), ft_strlen(in) + msh_cs(in, qf, -1, 0) + 1);
	while (in[++i] != '\0')
	{
		qf = msh_quote_flag(in[i], qf);
		if (qf == 1 || qf == 2 || !msh_checktype_input(in, i)
			|| (msh_checktype_input(in, i) == 1 && qf == 0)
			|| (msh_checktype_input(in, i) == 4 && qf == 0))
			result[++j] = in[i];
		else if (msh_checktype_input(in, i) == 2)
		{
			result[++j] = in[i];
			result[++j] = in[++i];
		}
		else if (msh_checktype_input(in, i) == 3)
		{
			result[++j] = in[i];
			result[++j] = in[++i];
		}
		if (msh_checktype_input(in, i) != 0 && qf == 0)
			result[++j] = ' ';
	}
	free(in);
	return (result);
}
