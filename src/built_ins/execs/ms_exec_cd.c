/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:57:11 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/29 19:54:19 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_set_pwds(t_vars *vars, char *path)
{
	int		env_index;
	char	*new_pwd;
	char	*tmp;

	if (msh_get_env_index(vars, "OLDPWD") == -1)
		msh_set_env_var(vars, "OLDPWD", "");
	env_index = msh_get_env_index(vars, "OLDPWD");
	tmp = msh_get_env_value(vars, msh_get_env_index(vars, "PWD"));
	new_pwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	msh_free_ptr(vars->envar[env_index]);
	vars->envar[env_index]
		= new_pwd;
	env_index = msh_get_env_index(vars, "PWD");
	new_pwd = ft_strjoin("PWD=", path);
	msh_free_ptr(vars->envar[env_index]);
	vars->envar[env_index] = new_pwd;
}

int	msh_cd_change_dir(t_vars *vars, char *path)
{
	msh_set_pwds(vars, path);
	chdir(path);
	msh_free_ptr(path);
	return (1);
}

void	msh_cd_go_home(t_vars *vars)
{
	char	*home_ref;
	int		env_index;

	env_index = msh_get_env_index(vars, "HOME");
	if (env_index < 0)
		ft_putendl_fd("cd: HOME env variable is not defined! ", 2);
	home_ref = msh_get_env_value(vars, env_index);
	msh_cd_change_dir(vars, home_ref);
}

//settear siemppre ret = NULL;
void	msh_cd_go_to_path(t_vars *vars, char *path, char *ret)
{
	char	cwd[PATH_MAX];

	if (path[0] == '~')
		path = msh_get_env_value(vars, msh_get_env_index(vars, "HOME"));
	if (chdir(path) != 0)
	{
		msh_errors_cd(path, ": No such file or directory\n");
		g_return_status = 1;
	}
	else
	{
		ret = getcwd(cwd, PATH_MAX);
		if (!ret)
		{
			msh_errors_cd(path, ": No such file or directory\n");
			g_return_status = 1;
		}
		else
		{
			ret = ft_strdup(cwd);
			msh_set_pwds(vars, ret);
			free(ret);
		}
	}
}

void	msh_exec_cd(t_cmd *cmd, t_vars *vars)
{
	int	index;

	index = -1;
	if (cmd)
	{
		if (cmd->argc == 1)
			msh_cd_go_home(vars);
		else if (cmd->argc == 2)
			msh_cd_go_to_path(vars, cmd->argv[1], NULL);
		else
			ft_putendl_fd("cd: Too many arguments ", 2);
	}
}
