/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:12:45 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/23 20:39:58 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

// void	msh_count_tokens_extra_two(
// 	char *input, int *tokens, t_quotes quotes, int c
// 	)
// {
// 	if (msh_chr_can_be_separator(input[c])
// 		&& !quotes.quote && !quotes.miniquote)
// 	{
// 		if ((input[c] == '<' && input[c + 1] == '<')
// 			|| (input[c] == '>' && input[c + 1] == '>'))
// 			c++;
// 		tokens++;
// 	}
// }

// void	msh_count_tokens_extra(
// 	char *input, int *tokens, t_quotes quotes, int c
// 	)
// {
// 	if (!msh_chr_can_be_separator(input[c]))
// 	{
// 		tokens++;
// 		while (input[c] && (!msh_chr_can_be_separator(input[c])
// 				|| (msh_chr_can_be_separator(input[c])
// 					&& (quotes.quote || quotes.miniquote))))
// 		{
// 			c++;
// 			msh_update_quotes_status(&quotes, input[c]);
// 		}
// 	}
// }

// int	msh_count_tokens(char *input)
// {
// 	int				tokens;
// 	t_quotes		quotes;
// 	int				c;

// 	c = 0;
// 	tokens = 0;
// 	msh_init_quotes_struct(&quotes);
// 	while (input[c])
// 	{
// 		msh_update_quotes_status(&quotes, input[c]);
// 		msh_count_tokens_extra(input, &tokens, quotes, c);
// 		msh_count_tokens_extra_two(input, &tokens, quotes, c);
// 		if (input[c] != '\0')
// 			c++;
// 		if (input[c] == ' ' && !quotes.quote && !quotes.miniquote)
// 			c++;
// 	}
// 	return (tokens);
// }

// int	msh_how_many_argv_have_the_cmd(char *input)
// {
// 	t_quotes	quotes;
// 	int			num;
// 	int			end;
// 	int			c;

// 	c = -1;
// 	num = 0;
// 	end = 0;
// 	msh_init_quotes_struct(&quotes);
// 	while (input[++c])
// 	{
// 		msh_update_quotes_status(&quotes, input[c]);
// 		if (input[c] != ' ' && ((input[c + 1] == ' '
// 					&& !quotes.quote && !quotes.miniquote)
// 				|| input[c + 1] == '\0' ))
// 		{
// 			num++;
// 		}
// 	}
// 	return (num);
// }

// char	**msh_split_cmd_argvs(char *input, int argc)
// {
// 	t_quotes	quotes;
// 	int			start;
// 	int			c;
// 	int			num;
// 	char		**result;

// 	c = -1;
// 	start = 0;
// 	num = 0;
// 	result = malloc(sizeof(char *) * (argc + 1));
// 	msh_init_quotes_struct(&quotes);
// 	while (input[++c])
// 	{
// 		if (msh_is_startarg(input, c, &quotes))
// 			start = c;
// 		msh_update_quotes_status(&quotes, input[c]);
// 		if (msh_is_endarg(input, c, &quotes))
// 		{
// 			result[num] = ft_substr(input, start, c - start + 1);
// 			num++;
// 		}
// 	}
// 	result[num] = NULL;
// 	return (result);
// }
