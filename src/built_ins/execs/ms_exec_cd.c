/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:57:11 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/19 20:36:32 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

int	msh_cd_change_dir(t_vars *vars, char *path)
{
	int		env_index;
	char	*new_pwd;

	// printf("el actual PWD es %s\n", vars->envar[env_index]);

	// ? Here we store current PWD in OLDPWD and set new PWD to home_Redls
	
	// * Store NEW PWD
	env_index =	msh_get_env_index(vars, "PWD");
	new_pwd = ft_strjoin("PWD=",path);
	//free(vars->envar[env_index]);
	msh_free_ptr(vars->envar[env_index]);
	vars->envar[env_index] = new_pwd;
	// * change dir
	chdir(path);
	// TODO store OLD_PWD . REUSE UNSET
	// ? debug
	msh_print_env_vars(vars,"");
	// free(new_pwd);
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

void	msh_exec_cd(t_cmd *cmd, t_vars *vars)
{
	int	index;

	index = -1;
	if (cmd)
	{
		if (cmd->argc == 1)
			msh_cd_go_home(vars);
		else if (cmd->argc == 2)
			printf("go some other place");
		else
			ft_putendl_fd("cd: Too many arguments ", 2);
	}
} // ? This function should return EXIT_SUCCESS or 0 ?

// * STDOUT_FILENO = 1