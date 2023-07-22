/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:30:28 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/22 20:23:34 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_do_split_input_in_cmds_extra(t_vars *v, char **splitted, char *cmd)
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

char	**msh_do_split_input_in_cmds(t_vars *v, char **splitted, char *cmd)
{
	while (v->input[v->c->c1])
	{
		msh_update_quotes_status(v->quotes, v->input[v->c->c1]);
		if (msh_chr_can_be_separator(v->input[v->c->c1])
			&& !v->quotes->quote && !v->quotes->miniquote)
			msh_do_split_input_in_cmds_extra(v, splitted, cmd);
		else
		{
			if (v->input[v->c->c1] == ' '
				&& !v->quotes->quote && !v->quotes->miniquote)
			{
				if (!msh_chr_can_be_separator(v->input[v->c->c1 + 1]))
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

t_cmd	*create_token(char *input, int index)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	new->argc = msh_how_many_argv_have_the_cmd(input);
	new->argv = msh_split_cmd_argvs(input, new->argc);
	new->is_separator = msh_chr_can_be_separator(new->argv[0][0]);
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






