/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:16:13 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/23 16:43:06 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_atoi_extra(char *str, int *error, int *counter)
{
	int	*i;

	i = counter;
	while (str[*i])
	{
		if (str[*i] != ' ' && str[*i] != '\t')
		{
			msh_errors_exit(str, ": numeric argument required\n");
			*error = 1;
			break ;
		}
		i++;
	}
}

int	msh_atoi(char *str, int *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && msh_is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (msh_check_out_range(neg, num, error))
			break ;
		i++;
	}
	msh_atoi_extra(str, error, &i);
	return (num * neg);
}

int	msh_check_exit_param(char *param, int *error)
{
	unsigned long long	i;

	i = 0;
	while (msh_is_space(param[i]))
		i++;
	if (param[i] == '\0')
		*error = 1;
	if (param[i] == '-' || param[i] == '+')
		i++;
	if (!ft_isdigit(param[i]))
	{
		msh_errors_exit(param, ": numeric argument required\n");
		*error = 1;
		return (0);
	}
	i = msh_atoi(param, error);
	return (i);
}

void	msh_exec_exit_extra(t_cmd *cmd, int *error)
{
	if (ft_strcmp(cmd->argv[1], "18446744073709551616") == 0)
	{
		msh_errors_exit(cmd->argv[1], ": numeric argument required\n");
		g_return_status = 255;
		return ;
	}
	g_return_status = msh_check_exit_param(cmd->argv[1], error);
	if (error)
		g_return_status = 255;
}

void	msh_exec_exit(t_cmd *cmd, t_vars *vars)
{
	int	error;

	(void)vars;
	vars->looping = 0;
	error = 0;
	if (cmd->argc == 1)
		g_return_status = 0;
	else if (cmd->argc == 2)
		msh_exec_exit_extra(cmd, &error);
	else
	{
		vars->looping = 1;
		msh_check_exit_param(cmd->argv[1], &error);
		if (error == 1)
		{
			g_return_status = 255;
			return ;
		}
		msh_errors_exit("", "too many arguments\n");
		g_return_status = 1;
	}
}
