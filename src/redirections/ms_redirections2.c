/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:08:07 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/24 20:52:34 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_quote_flag(char input, int flag)
{
	if (input == '\'' && flag == 0)
		return (1);
	else if (input == '\'' && flag == 1)
		return (0);
	else if (input == '\"' && flag == 0)
		return (2);
	else if (input == '\"' && flag == 2)
		return (0);
	return (flag);
}

int	msh_is_redirect2(char *tcmd)
{
	if (ft_strcmp(tcmd, "<") == 0)
		return (1);
	else if (ft_strcmp(tcmd, ">") == 0)
		return (2);
	else if (ft_strcmp(tcmd, ">>") == 0)
		return (3);
	else if (ft_strcmp(tcmd, "<<") == 0)
		return (4);
	return (0);
}

//start qflag always at 0
int	msh_count_redir(char *input, int qflag)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		qflag = msh_quote_flag(input[i], qflag);
		if (qflag == 1 || qflag == 2)
			continue ;
		if ((input[i] == '>' && input[i + 1] != '>')
			|| (input[i] == '<' && input[i + 1] != '<'))
			count ++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			i ++;
			count ++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			i ++;
			count ++;
		}
	}
	return (count);
}

//set i always at -1
char	*msh_reorder_redirs2(char *cmd, int nmb_redirs, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	**tcmds;

	tcmds = ft_qsplit(cmd, ' ', 0, 0);
	while (tcmds[++i] != NULL && nmb_redirs > 0)
	{
		if (msh_is_redirect2(tcmds[i]))
		{
			j = i + 2;
			tmp = tcmds[i];
			tmp2 = tcmds[i + 1]; 
			while (tcmds[j] != NULL)
			{
				tcmds[j - 2] = tcmds[j];
				tcmds[j - 1] = tcmds[j + 1];
				j += 1;
			}
			tcmds[j - 2] = tmp;
			tcmds[j - 1] = tmp2;
			i = -1;
			nmb_redirs --;
		}
	}
	return (msh_set_final_cmd(tcmds, cmd));
}

void	msh_reorder_redirs(t_vars *vars)
{
	char	**pipes;
	int		i;

	i = 0;
	pipes = ft_split(vars->input, '|');
	if (pipes[0] == NULL)
		return ;
	while (pipes[i] != NULL)
	{
		if (msh_count_redir(pipes[i], 0) > 0)
			pipes[i] = msh_reorder_redirs2(pipes[i],
					msh_count_redir(pipes[i], 0), -1, 0);
		i++;
	}
	i = 0;
	free (vars->input);
	vars->input = ft_strdup("");
	while (pipes[i] != NULL)
	{
		vars->input = ft_joinloc(vars->input, pipes[i]);
		if (pipes[i + 1] != NULL)
			vars->input = ft_joinloc(vars->input, ft_strdup("|"));
		i++;
	}
	free (pipes);
}
