/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:40:12 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/19 17:15:30 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

void	msh_echo_print(char **args, int n_flags, int index)
{
	int	c;

	if (!args[index])
	{
		if (!n_flags)
			ft_putchar_fd('\n', 1);
		return ;
	}// ? if there is no string and there ar enot n flags just print \n
	while (args[index])
	{
		//printf("el argumento de este echo es %s y n_flags esta seteado a %d\n", args[index], n_flags);
		//ft_putstr_fd(args[index], 1);
		c = -1;
		while (args[index][++c])
		{
			if (args[index][c] != '"' && args[index][c] != '\'')
				ft_putchar_fd(args[index][c], 1);
		}
		if (args[index + 1])
			ft_putchar_fd(' ', 1);
		else if (!args[index + 1] && !n_flags)
			ft_putchar_fd('\n', 1);
		index++;
	}
}

int	msh_echo_has_n_flag(char *arg)
{
	int	i;
	int	n_flag;

	n_flag = 0; // ? init bool to false
	i = 0; // ? set counter
	if (arg[i] != '-')
		return (n_flag); // ? if flag does no start with - just fuck it
	i++; // ? get to 1
	while (arg[i] && arg[i] == 'n')
		i++; // ? clear all n's
	if (arg[i] == '\0')
		n_flag = 1; // ? if we reach the end of string set flag to true
	return (n_flag);
}

void	msh_exec_echo(t_cmd *cmd, t_vars *vars)
{
	int	index;
	int	n_flags;

	(void)vars;
	// ? start after "echo" word
	index = 0; //? Skip de first argument which is echo itself
	n_flags = 0;
	if (cmd)
	{
		while (cmd->argv[++index] && msh_echo_has_n_flag(cmd->argv[index]))
			n_flags = 1;
	}
	msh_echo_print(cmd->argv, n_flags, index);
} // ? This function should return EXIT_SUCCESS or 0 ?

// * STDOUT_FILENO = 1

