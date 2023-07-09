/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:45:26 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/09 18:58:34 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

int	msh_get_env_index(t_vars *vars, char *env_name)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(env_name, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (vars->envar[i])
	{
		if (ft_strncmp(tmp, vars->envar[i], ft_strlen(tmp)) == 0)
		{
			msh_free_ptr(tmp);
			return (i);
		}
		i++;
	}
	msh_free_ptr(tmp);
	return (-1);
}

char	*msh_get_env_value(t_vars *vars, int env_index)
{
	int		c;
	char	*env_value;

	c = 0;
	env_value = NULL;
	while (vars->envar[env_index][c] != '=')
		c++;
	while (vars->envar[env_index][c++])
		env_value = msh_strjoinchr(env_value, vars->envar[env_index][c]);
	return (env_value);
}

void	msh_print_env_value(t_vars *vars, int env_index)
{
	int	c;

	
	// msh_print_env_vars(vars, "");
	
	c = 0;
	while (vars->envar[env_index][c] != '=')
		c++;
	c++;
	while (vars->envar[env_index][c])
	{
		ft_putchar_fd(vars->envar[env_index][c], 1);		
		c++;
	}
	ft_putchar_fd('\n', 1);
	g_return_status = 0; // TODO this returns -11 ?
}

void	msh_exec_pwd(t_cmd *cmd, t_vars *vars)
{
	int	env_index;
	(void)cmd;	
	env_index = msh_get_env_index(vars, "PWD");
	msh_print_env_value(vars, msh_get_env_index(vars, "PWD"));
}

// * STDOUT_FILENO = 1