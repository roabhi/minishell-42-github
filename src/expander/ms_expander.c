/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:50:35 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/23 18:24:42 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_advance_from_env_var(char *arg)
{
	int	i;

	i = 1;
	if (arg[1] == '?')
		return (2);
	while (arg[i] && arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
		i++;
	return (i);
}

char	*msh_read_env_name(char *arg)
{
	int		i;
	char	*index_name;

	i = 1;
	index_name = NULL;
	while (arg[i] && arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
	{
		index_name = msh_strjoinchr(index_name, arg[i]);
		i++;
	}
	return (index_name);
}

void	msh_expand_env_var(t_vars *vars, char *arg, char **new_arg)
{
	char	*env_index_name;
	char	*value;
	int		env_index;
	int		i;

	i = 0;
	if (arg[1] != '?')
	{
		env_index_name = msh_read_env_name(arg);
		env_index = msh_get_env_index(vars, env_index_name);
		if (env_index == -1)
		{
			free(env_index_name);
			return ;
		}
		value = msh_get_env_value(vars, env_index);
		free(env_index_name);
	}
	else
		value = ft_itoa(g_return_status);
	while (value[i])
		*new_arg = msh_strjoinchr(*new_arg, value[i++]);
	free(value);
}

void	msh_expand_argv(t_vars *vars, char **argv, int c)
{
	char		*new_arg;
	int			i;
	t_quotes	quotes;

	msh_init_quotes_struct(&quotes);
	i = 0;
	new_arg = NULL;
	while (argv[c][i])
	{
		msh_update_quotes_status(&quotes, argv[c][i]);
		if ((argv[c][i] == '"' && !quotes.miniquote)
			|| (argv[c][i] == '\'' && !quotes.quote))
			i++;
		else if (argv[c][i] == '$' && !quotes.miniquote)
		{
			if (!argv[c][i + 1])
				return ;
			msh_expand_env_var(vars, &argv[c][i], &new_arg);
			i += msh_advance_from_env_var(&argv[c][i]);
		}
		else
			new_arg = msh_strjoinchr(new_arg, argv[c][i++]);
	}
	free(argv[c]);
	argv[c] = new_arg;
}

void	msh_expander(t_vars *vars)
{
	t_cmd	*first;
	int		c;
	int		x;

	first = vars->cmd;
	c = -1;
	while (first)
	{
		while (first->argv[++c])
		{
			x = -1;
			while (first->argv[c][++x])
			{
				if (msh_argv_need_expansion(first->argv[c][x]))
				{
					msh_expand_argv(vars, first->argv, c);
					break ;
				}
			}
		}
		c = -1;
		first = first->next;
	}
}
