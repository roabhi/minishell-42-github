/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:30:28 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/24 19:12:05 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_how_many_argv_have_the_cmd(char *input)
{
	t_quotes	quotes;
	int			num;
	int			end;
	int			c;

	c = -1;
	num = 0;
	end = 0;
	msh_init_quotes_struct(&quotes);
	while (input[++c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ' && ((input[c + 1] == ' '
					&& !quotes.quote && !quotes.miniquote)
				|| input[c + 1] == '\0' ))
			num++;
	}
	return (num);
}

char	**msh_split_cmd_argvs(char *input, int argc)
{
	t_quotes	quotes;
	int			start;
	int			c;
	int			num;
	char		**result;

	c = -1;
	start = 0;
	num = 0;
	result = malloc(sizeof(char *) * (argc + 1));
	msh_init_quotes_struct(&quotes);
	while (input[++c])
	{
		if (msh_is_startarg(input, c, &quotes))
			start = c;
		msh_update_quotes_status(&quotes, input[c]);
		if (msh_is_endarg(input, c, &quotes))
		{
			result[num] = ft_substr(input, start, c - start + 1);
			num++;
		}
	}
	result[num] = NULL;
	return (result);
}

t_cmd	*create_token(char *input, int index)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	new->argc = msh_how_many_argv_have_the_cmd(input);
	new->argv = msh_split_cmd_argvs(input, new->argc);
	new->is_separator = msh_chr_is_sep(new->argv[0][0]);
	new->index = index;
	return (new);
}

char	**msh_prepare_splitted_input_in_cmds(t_vars *vars)
{
	char			**s;
	t_counters		counters;
	char			*cmd;
	t_quotes		quotes;

	counters.c1 = 0;
	counters.c2 = 0;
	cmd = NULL;
	vars->c = &counters;
	msh_init_quotes_struct(&quotes);
	vars->quotes = &quotes;
	s = malloc(sizeof(char *) * (msh_count_tokens(vars->input) + 1));
	if (!s)
		return (NULL);
	return (msh_do_split_input_in_cmds(vars, s, cmd));
}

// ! Entry point

t_cmd	*msh_tokenize(t_vars *vars)
{
	t_cmd	*my_cmd_list;
	t_cmd	*new;
	t_cmd	*last;
	int		c;
	char	**splitted_cmds;

	c = 0;
	my_cmd_list = NULL;
	splitted_cmds = msh_prepare_splitted_input_in_cmds(vars);
	vars->tokens = splitted_cmds;
	while (splitted_cmds[c])
	{
		new = create_token(splitted_cmds[c], c);
		if (!my_cmd_list)
			my_cmd_list = new;
		else
			last->next = new;
		last = new;
		last->next = NULL;
		c++;
	}
	return (my_cmd_list);
}
