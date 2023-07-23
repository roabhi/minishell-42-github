/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:11:18 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/23 16:43:44 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

int	msh_set_env_var(t_vars *vars, char *key, char *value)
{
	int		env_var_index;
	char	*new_env_var;

	env_var_index = msh_get_env_index(vars, key);
	if (value == NULL)
		value = "";
	new_env_var = ft_strjoin("=", value);
	if (!new_env_var)
		return (0);
	if (env_var_index != -1 && vars->envar[env_var_index])
	{
		msh_free_ptr(vars->envar[env_var_index]);
		vars->envar[env_var_index] = ft_strjoin(key, new_env_var);
	}
	else
	{
		env_var_index = msh_get_env_vars_length(vars);
		vars->envar = msh_realloc_env_vars(vars, env_var_index + 1);
		if (!vars->envar)
			return (0);
		vars->envar[env_var_index] = ft_strjoin(key, new_env_var);
	}
	msh_free_ptr(new_env_var);
	return (1);
}

char	**msh_get_env_var_key_value_pair(char *str)
{
	char	**tmp;
	char	*eq_to_end_str;	

	eq_to_end_str = ft_strchr(str, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(str, 0, eq_to_end_str - str);
	tmp[1] = ft_substr(eq_to_end_str, 1, ft_strlen(eq_to_end_str));
	tmp[2] = 0;
	return (tmp);
}

void	msh_exec_export_extra(
	t_cmd *cmd, t_vars *vars, char **new_env_var, int c
	)
{
	if (!msh_is_valid_env_var_key(cmd->argv[c]))
	{
		msh_errors_export(cmd->argv[c], "': not a valid identifier\n");
		g_return_status = 1; 
	}
	else if (ft_strchr(cmd->argv[c], '=') != NULL)
	{
		new_env_var = msh_get_env_var_key_value_pair(cmd->argv[c]);
		msh_set_env_var(vars, new_env_var[0], new_env_var[1]);
		msh_free_ptr(new_env_var[0]);
		msh_free_ptr(new_env_var[1]);
		msh_free_ptr(new_env_var);
		g_return_status = 0; 
	}
	else
		msh_set_env_var(vars, cmd->argv[c], "");
}

void	msh_exec_export(t_cmd *cmd, t_vars *vars)
{
	int		c;
	char	**new_env_var;

	c = 0;
	new_env_var = NULL;
	if (cmd->argc == 1)
		msh_print_env_vars(vars, "declare -x ");
	else
	{
		while (cmd->argv[++c])
		{
			msh_exec_export_extra(cmd, vars, new_env_var, c);
		}
	}
}
