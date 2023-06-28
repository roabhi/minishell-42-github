/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:30:28 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/28 22:55:46 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

char	**msh_do_split_input_in_cmds(t_vars *v, char **splitted, char *cmd)
{
	while (v->input[v->c->c1])
	{
		msh_update_quotes_status(v->quotes, v->input[v->c->c1]);
		if (msh_chr_can_be_separator(v->input[v->c->c1])
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






/**
 * @brief function para segementar el string
 * 
 * @param input 
 * @return int 
 */

/*
	printf("string ends in %d\n", c);
	printf("el legnht de input es:%zu\n",  ft_strlen(input));
	printf("el input es |%s|\n", input);
	printf("I detected %d needed tokens for this input\n", tokens);
	printf("1 start token in: %d that is %c\n", c, input[c]);
*/

int	msh_count_tokens(char *input)
{
	int				tokens;
	t_quotes		quotes;
	int				c;

	c = 0;
	tokens = 0;
	msh_init_quotes_struct(&quotes);
	while (input[c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (!msh_chr_can_be_separator(input[c]))
		{
			tokens++;
			while (input[c] && (!msh_chr_can_be_separator(input[c])
					|| (msh_chr_can_be_separator(input[c])
						&& (quotes.quote || quotes.miniquote))))
			{
				c++;
				msh_update_quotes_status(&quotes, input[c]);
			}
		}
		if (msh_chr_can_be_separator(input[c])
			&& !quotes.quote && !quotes.miniquote)
		{
			if ((input[c] == '<' && input[c + 1] == '<')
				|| (input[c] == '>' && input[c + 1] == '>'))
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
	//printf("Input es |%s|\n", input);
	while (input[++c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ' && ((input[c + 1] == ' '
					&& !quotes.quote && !quotes.miniquote)
				|| input[c + 1] == '\0' ))
		{
					num++;
		}
	}
	return (num);
}		
//  hola "que tal " como estas | echo hola  a << b  


// Esto me puede servir para generar los argv de cada token
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
					//printf("result[num] = |%s|\n", result[num]);
					num++;
		}
	}
	result[num] = NULL;
	return (result);
}

//msh_split_cmd_argvs
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
	// int i;
	// i = 0;
	// while(splitted_cmds[i])
	// {
	// 	// printf("splitted |%s|\n", splitted_cmds[i]);
	// 	i++;
	// }
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
	// printf("Saliendo en msh_tokenize\n");
	return (my_cmd_list);
}



