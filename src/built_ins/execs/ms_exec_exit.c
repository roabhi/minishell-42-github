/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:16:13 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/28 22:39:46 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

// function que determina si el argumento es valido. Ha de ser un numero
// Si es un numero saldremos con el valor de ese numero
// Si no es un numero, saldremos con 255

int	msh_check_out_range(int neg, unsigned long long num, int *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = 1;
	return (*error);
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
	while(str[i] == '-')
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
	while (str[i])
	{
		if(str[i] != ' ' && str[i] != '\t')
		{
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			*error = 1;
			break ;
		}
		i++;
	}
	return (num * neg);
}


int	msh_check_exit_param(char *param, int *error)
{
	unsigned long long i;

	i = 0;
	while (msh_is_space(param[i]))
		i++;
	if (param[i] == '\0')
	{
		printf("hay error 1");
		*error = 1;
		//ft_putendl_fd("No content param",2);
	}
	if (param[i] == '-' || param[i] == '+')
		i++;
	if (!ft_isdigit(param[i]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, param, ft_strlen(param));
		write(2, ": numeric argument required\n", 28);
		*error = 1;
		return 0;
		//ft_putendl_fd("Number required",2);
	}
	// while (param[i])
	// {
	// 	if (!ft_isdigit(param[i]))
	// 	{
	// 		*error = 1;
	// 		//ft_putendl_fd("Number required or spaces present",2);
	// 	}
	// 	i++;
	// }
	i = msh_atoi(param, error);
	return (i);
	//g_return_status = 255;
}


void	msh_exec_exit(t_cmd *cmd, t_vars *vars)
{
	(void)vars;
	vars->looping = 0;
	int error;

	error = 0;
	if(cmd->argc == 1)
	{
		g_return_status = 0;
	}
	else if (cmd->argc == 2)
	{
		if(ft_strcmp(cmd->argv[1] , "18446744073709551616") == 0){
			write(2, "minishell: exit: ", 17);
			write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
			write(2, ": numeric argument required\n", 28);
			g_return_status = 255;
			return;
		}
		g_return_status = msh_check_exit_param(cmd->argv[1], &error);
		if (error)
			g_return_status = 255;
	}
	else{
		vars->looping = 1;
		//validar numero, si no es bueno salir con 255
		// si es valido con el atoi de ese numero
		msh_check_exit_param(cmd->argv[1], &error);
		if (error == 1){
			g_return_status = 255;
			return;
		}
		write(2, "minishell: exit: too many arguments\n", 36);
		g_return_status = 1; // ? More than 2 arguments
	}
}
