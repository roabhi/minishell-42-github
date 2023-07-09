/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:11:18 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/06 22:23:19 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

/**
 * @brief function that updates or creates a new env var
 * 
 * @param vars main structure with access to envvar
 * @param key the string with the key to look for or insert
 * @param value the value to be set to the new env var. Can be empty
 * @return int 1 if success 0 if error
 */

int	msh_set_env_var(t_vars *vars, char *key, char *value)
{
	int		env_var_index;
	char	*new_env_var;

	env_var_index = msh_get_env_index(vars, key);
	// ? Set env value to empty in case value it is not defined
	if (value == NULL)
		value = "";
	// ? append = to the value
	new_env_var = ft_strjoin("=", value);
	if (!new_env_var)
		return (0);
	// ? update value for existing env var
	if (env_var_index != -1 && vars->envar[env_var_index])
	{
		msh_free_ptr(vars->envar[env_var_index]);
		vars->envar[env_var_index] = ft_strjoin(key, new_env_var);
	}
	// ? if we are inserting new env var
	else
	{
		env_var_index = msh_get_env_vars_length(vars);
		// ? create a new env vars structure with an additional space for the new var
		vars->envar = msh_realloc_env_vars(vars, env_var_index + 1);
		if (!vars->envar)
			return (0);
		// ? insert new env var
		vars->envar[env_var_index] = ft_strjoin(key, new_env_var);
	}
	msh_free_ptr(new_env_var);
	return (1);
}

char	**msh_get_env_var_key_value_pair(char *str)
{
	char	**tmp;
	char	*eq_to_end_str;	

	// ? get string after position of the = char
	eq_to_end_str = ft_strchr(str, '='); 
	// ? allocate mem based on 2 strings + '\0'
	tmp = malloc(sizeof * tmp * (2 + 1));
	// printf("El char [0] del nuevo string es devuelto por ft_strchr de %s es %s", str, ft_substr(str, 0, eq_to_end_str - str));
	// ? Create a substring for the [0] index for tmp with just the key
	tmp[0] = ft_substr(str, 0, eq_to_end_str - str);
	// ? Create a substring for the [1] index for tmp with just the value
	tmp[1] = ft_substr(eq_to_end_str, 1, ft_strlen(eq_to_end_str));
	// ? Close the main pointer with a null
	tmp[2] = 0;
	return (tmp);
}

void	msh_exec_export(t_cmd *cmd, t_vars *vars)
{
	int		c;
	char	**new_env_var;

	c = 0;
	if (cmd->argc == 1)
		msh_print_env_vars(vars, "declare -x ");
	else
	{
		while (cmd->argv[++c])
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
	}
}
