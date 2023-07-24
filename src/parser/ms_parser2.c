/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:07:56 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/24 20:58:31 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

// put always qflag = 0;
char	*msh_add_space_between_input(char *input, int qflag)
{
	int		i;
	int		j;
	int		count;
	char	*result;

	i = -1;
	j = -1;
	count = 0;
	while (input[++i] != '\0')
	{
		qflag = msh_quote_flag(input[i], qflag);
		if (qflag == 1 || qflag == 2)
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
	i = -1;
	result = ft_calloc(sizeof(char), ft_strlen(input) + count + 1);
	while (input[++i] != '\0')
	{
		qflag = msh_quote_flag(input[i], qflag);
		if (qflag == 1 || qflag == 2)
		{
			result[++j] = input[i];
			continue ;
		}
		if (((input[i] == '>' && input[i + 1] != '>')
				|| (input[i] == '<' && input[i + 1] != '<'))
			&& input[i + 1] != ' ')
		{
			result[++j] = input[i];
			result[++j] = ' ';
		}
		else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] != ' ')
		{
			result[++j] = input[i];
			result[++j] = input[++i];
			result[++j] = ' ';
		}
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] != ' ')
		{
			result[++j] = input[i];
			result[++j] = input[++i];
			result[++j] = ' ';
		}
		else if ((input[i] != ' ' || input[i] != '>' || input[i] != '<')
			&& (input[i + 1] == '>' || input[i + 1] == '<') 
			&& input[i + 2] != ' ')
		{
			result[++j] = input[i];
			result[++j] = ' ';
		}
		else
		{
			result[++j] = input[i];
		}
	}
	free(input);
	return (result);
}
