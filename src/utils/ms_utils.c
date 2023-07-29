/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:21:49 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/29 18:08:25 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void	msh_set_vars(t_vars *vars, char *input)
{
	vars->looping = 1;
	g_return_status = 0;
	vars->prompt = ft_calloc(ft_strlen(input) + 1, 1);
	vars->inpli = NULL;
	ft_strlcpy(vars->prompt, input, ft_strlen(input));
}

void	msh_str_to_lower(char *str)
{
	int	c;

	c = 0;
	while (str[c])
	{
		if (str[c] <= 90 && str[c] >= 65)
			str[c] = str[c] + 32;
		else
			str[c] = str[c];
		c++;
	}
}

void	msh_init_quotes_struct(t_quotes *quote_struct)
{
	quote_struct->quote = 0;
	quote_struct->miniquote = 0;
}

void	msh_update_quotes_status(t_quotes *quotes, char c)
{
	if (c == '"' && quotes->quote == 0 && quotes->miniquote != 1)
		quotes->quote = 1;
	else if (c == '"' && quotes->quote == 1)
		quotes->quote = 0;
	if (c == '\'' && quotes->miniquote == 0 && quotes->quote != 1)
		quotes->miniquote = 1;
	else if (c == '\'' && quotes->miniquote == 1)
		quotes->miniquote = 0;
}

char	*msh_strjoinchr(char *str, char ch)
{
	char	*copy;
	int		c;

	c = -0;
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	copy = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!copy)
		return (msh_free_return_null(copy));
	while (str[c])
	{
		copy[c] = str[c];
		c++;
	}
	copy[c] = ch;
	copy[c + 1] = '\0';
	free(str);
	return (copy);
}
