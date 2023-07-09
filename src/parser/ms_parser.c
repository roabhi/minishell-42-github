/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:07:56 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/06 21:34:44 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

char	*msh_clean_irrelveant_spaces_in_input(char *input)
{
	char		*new_input;
	t_quotes	quotes;
	size_t		c;

	msh_init_quotes_struct(&quotes);
	new_input = NULL;
	c = -1;
	while (input[++c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ')
			new_input = msh_strjoinchr(new_input, input[c]);
		else if (input[c] == ' ' && (quotes.quote == 1
				|| quotes.miniquote == 1))
			new_input = msh_strjoinchr(new_input, input[c]);
		else if (input[c] == ' ' && (quotes.quote == 0
				|| quotes.miniquote == 0))
		{
			new_input = msh_strjoinchr(new_input, input[c]);
			while (input[c] == ' ' && input[c + 1] == ' ')
				c++;
		}
	}
	free(input);
	return (new_input);
}

int	msh_malformed_quotes(char *input)
{
	int			c;
	t_quotes	quotes;

	c = -1;
	msh_init_quotes_struct(&quotes);
	while (input[++c])
		msh_update_quotes_status(&quotes, input[c]);
	if (quotes.quote == 1 || quotes.miniquote == 1)
	{
		//write(2, "Malformed input. Please close your quotes\n", 42);
		ft_putendl_fd("Minishell: Malformed input, please close your quotes", 2);
		return (1);
	}
	return (0);
}

// ! Entry point
char	*msh_sanitize_input(char *input)
{
	char	*trimmed_input;

	if (msh_malformed_quotes(input))
	{
		free(input);
		return (NULL);
	}
	trimmed_input = ft_strtrim(input, " ");
	// ! comment for testing
	free(input);
	input = msh_clean_irrelveant_spaces_in_input(trimmed_input);
	return (input);
}



