/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:50:35 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/26 22:34:28 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_advance_from_env_var(char *arg)
{
	int	i;

	i = 1;
	while (arg[i] && arg[i] != '"' && arg[i] != '\'')
	{
		i++;
	}
	return (i);
}

char	*msh_read_env_name(char *arg)
{
	int		i;
	char	*index_name;

	i = 1;
	index_name = NULL;
	while (arg[i] && arg[i] != '"' && arg[i] != '\'')
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
	env_index_name = msh_read_env_name(arg);
	env_index = msh_get_env_index(vars, env_index_name);
	value = msh_get_env_value(vars, env_index);
	free(env_index_name);
	while (value[i])
	{
		*new_arg = msh_strjoinchr(*new_arg, value[i]);
		i++;
	}
	free(value);
}

void	msh_expand_argv(t_vars *vars, char **argv, int c)
{
	char		*new_arg;
	int			i;
	t_quotes	quotes;

	printf("\narg to expand |%s|\n", argv[c]);
	msh_init_quotes_struct(&quotes);
	i = 0;
	(void)vars;
	new_arg = NULL;
	while (argv[c][i])
	{
		msh_update_quotes_status(&quotes, argv[c][i]);
		if (argv[c][i] == '"' && !quotes.miniquote)
		{
			i++;
			continue ;
		}
		if (argv[c][i] == '\'' && !quotes.quote)
		{
			i++;
			continue ;
		}
		if (argv[c][i] == '$' && !quotes.miniquote)
		{
			// msh_expand_env_var(vars, &argv[c][i], &new_arg);
			// i += msh_advance_from_env_var(&argv[c][i]);
			// continue ;
		}
		// new_arg = msh_strjoinchr(new_arg, argv[c][i]);
		i++;
	}
	free(argv[c]);
	argv[c] = new_arg;
	printf("arg after expander |%s|\n", argv[c]);
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
		// printf("El token con indice %d es un separador? -> %d\n", first->index, first->is_separator);
		//printf("\n+++++++ command %d +++++++\n", first->index);
		while (first->argv[++c])
		{
			//printf("token %d |%s|\n", c, first->argv[c]);
			x = -1;
			while (first->argv[c][++x])
			{
				//printf("El char es %c\n", first->argv[c][x]);
				if (msh_argv_need_expansion(first->argv[c][x])){
					printf("El argumento %s necesita ser expandido? -> %d", first->argv[c], msh_argv_need_expansion(first->argv[c][x]));
					msh_expand_argv(vars, first->argv, c);
					break;
				}
			}
			printf("\n\n");
		}
		c = -1;
		first = first->next;
	}
}

// TODO Por cada comandp y por cada argumento del comando
// TODO hay que quitar los quotes y miniquotes
// TODO por cada caracter the cada argumento
// * si me encuentro $ ' "
// * hayq que expandir 
// TODO y expandir las variables de entorno


 //Si no hay ' " o $
	//"'hola'"
	//'hola'

	//"'$USER'"
	//'rabril'  

	// '      "$USER"'
	//      "$USER"