/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 17:18:31 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

//Global variable
int	g_return_status;

void	msh_set_init(t_vars *vars, char **envp)
{
	msh_set_vars(vars, "msh %  ");
	msh_store_env_own_vars(vars, envp);
}

int	msh_readline(t_vars *vars, int ac, char **av)
{
	msh_ignore_signals(vars, ac, av);
	vars->inpli = readline(vars->prompt);
	if (vars->inpli == NULL)
		return (0);
	return (1);
}

int	msh_check_inputline(t_vars *vars)
{
	if (vars->inpli[0] == '\0')
	{
		msh_free_memory_dynamic(vars, 2);
		return (0);
	}
	return (1);
}

//leaks check use "system("leaks minishell");" at the end before final return
int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	msh_set_init(&vars, envp);
	while (vars.looping)
	{
		if (msh_readline(&vars, ac, av))
		{
			if (!msh_check_inputline(&vars))
				continue ;
			add_history(vars.inpli);
			vars.input = msh_sanitize_input(vars.inpli);
			if (vars.input == NULL)
				continue ;
			vars.cmd = msh_tokenize(&vars);
			if (!msh_check_errors_syntax(&vars))
				continue ;
			msh_execute_main(&vars);
		}
		else
			vars.looping = 0;
	}
	ft_putendl_fd("exit", 1);
	msh_free_memory_dynamic(&vars, 3);
	return (g_return_status);
}
