/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:03:38 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/22 19:29:31 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../incl/mslib.h"

char	*msh_getpath_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i ++;
	i --;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0 && i != 0)
		i --;
	if (i == 0)
		return (NULL);
	return (envp[i]);
}

void	msh_getpath(t_vars *vars, char **envp)
{
	char	*path_line;
	int		i;

	path_line = msh_getpath_line(envp);
	if (path_line == NULL)
		path_line = "PATH=./";
	i = ft_strlen(path_line);
	path_line = ft_substr(path_line, 5, i);
	i = -1;
	vars->paths = ft_split(path_line, ':');
	free(path_line);
}

char	*msh_getpath_cmd(t_vars *vars, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*tmp;

	i = 0;
	path_cmd = NULL;
	while (vars->paths[i] != NULL)
	{
		tmp = ft_strjoin(vars->paths[i], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_cmd, F_OK) == 0)
			break ;
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	if (path_cmd == NULL)
	{
		printf("msh: %s: command not found\n", cmd);
		g_return_status = 127;
		return (NULL);
	}
	return (path_cmd);
}