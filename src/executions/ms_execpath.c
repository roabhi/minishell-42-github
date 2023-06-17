/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:03:38 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/17 18:35:40 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../incl/mslib.h"

char	*msh_getpath_line(char **envp)
{
	int	i;

	i = 0;
	write(1 , "enters get pathline\n", 20);
	while (envp[i] != NULL)
	{
		//write(1 , ft_itoa(i), ft_strlen(ft_itoa(i)));
		i ++;
	}
	write(1 , "middle get pathline\n", 20);
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

	write(1 , "enters get path\n", 16);
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
		return (NULL);
	}
	return (path_cmd);
}