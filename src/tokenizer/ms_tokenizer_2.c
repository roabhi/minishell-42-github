/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:12:45 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/24 15:43:35 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"




char	**msh_do_split_input_in_cmds(t_vars *v, char **splitted, char *cmd)
{
	while (v->input[v->c->c1])
	{
		msh_update_quotes_status(v->quotes, v->input[v->c->c1]);
		if (msh_chr_is_sep(v->input[v->c->c1])
			&& !v->quotes->quote && !v->quotes->miniquote)
		{
			if (cmd)
				splitted[v->c->c2++] = cmd;
			if (cmd)
				cmd = NULL;
			if (v->input[v->c->c1 + 1]
				&& ((v->input[v->c->c1] == '<' && v->input[v->c->c1 + 1] == '<')
					|| (v->input[v->c->c1] == '>'
						&& v->input[v->c->c1 + 1] == '>')))
				cmd = msh_strjoinchr(cmd, v->input[v->c->c1++]);
			cmd = msh_strjoinchr(cmd, v->input[v->c->c1]);
			splitted[v->c->c2++] = cmd;
			cmd = NULL;
		}
		else
		{
			if (v->input[v->c->c1] == ' '
				&& !v->quotes->quote && !v->quotes->miniquote)
			{
				if (!msh_chr_is_sep(v->input[v->c->c1 + 1]))
					cmd = msh_strjoinchr(cmd, v->input[v->c->c1]); 
			}
			else
				cmd = msh_strjoinchr(cmd, v->input[v->c->c1]);
		}
		v->c->c1++;
	}
	if (cmd != NULL)
		splitted[v->c->c2++] = cmd;
	splitted[v->c->c2] = NULL;
	return (splitted);
}

void	msh_count_tokens_not_separator(
	char *input, t_quotes quotes, int counter
	)
{
	int	c;

	c = counter;
	while (input[c] && (!msh_chr_is_sep(input[c])
			|| (msh_chr_is_sep(input[c])
				&& (quotes.quote || quotes.miniquote))))
	{
		c++;
		msh_update_quotes_status(&quotes, input[c]);
	}
}

int	msh_count_tokens_extra(char *input, t_quotes quotes)
{
	int	c;
	int	tokens;

	c = 0;
	tokens = 0;
	while (input[c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (!msh_chr_is_sep(input[c]))
		{
			tokens++;
			msh_count_tokens_not_separator(input, quotes, c);
		}
		if (msh_chr_is_sep(input[c]) && !quotes.quote && !quotes.miniquote)
		{
			if (msh_chr_is_double_redirection(input[c], input[c + 1]))
				c++;
			tokens++;
		}
		if (input[c] != '\0')
			c++;
		if (input[c] == ' ' && !quotes.quote && !quotes.miniquote)
			c++;
	}
	return (tokens);
}


int	msh_count_tokens(char *input)
{
	t_quotes		quotes;

	msh_init_quotes_struct(&quotes);
	return (msh_count_tokens_extra(input, quotes));
}
