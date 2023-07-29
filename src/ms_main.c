/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/29 19:10:18 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

//Global variable
int	g_return_status;

int	main2(t_vars *vars)
{
	msh_set_signals(2);
	if (vars->inpli[0] == '\0')
		free(vars->inpli);
	else
		add_history(vars->inpli);
	return (g_return_status);
}

int	main3(t_vars *vars)
{
	vars->input = msh_sanitize_input(vars->inpli);
	vars->cmd = msh_tokenize(vars);
	if (msh_errors_syntax(vars->cmd, NULL, 0) || vars->input == NULL)
	{
		msh_free_cmd_list(vars->cmd);
		msh_free_raw_array(vars->tokens);
		free(vars->input);
		return (g_return_status);
	}
	msh_free_cmd_list(vars->cmd);
	msh_free_raw_array(vars->tokens);
	vars->input = msh_add_space_between_input(vars->input, 0, -1, -1);
	msh_reorder_redirs(vars);
	vars->cmd = msh_tokenize(vars);
	if (vars->cmd != NULL)
	{
		msh_expander(vars);
		msh_execute_start(vars);
	}
	msh_clean_heredoc(vars);
	msh_free_cmd_list(vars->cmd);
	msh_free_raw_array(vars->tokens);
	free(vars->input);
	return (g_return_status);
}

//para testear leaks poner 	"system("leaks minishell");" antes del return final
int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	msh_set_vars(&vars, "msh %  ");
	if (!msh_store_env_own_vars(&vars, envp))
		return (-1);
	while (vars.looping)
	{
		vars.looping = 1;
		msh_ignore_signals(&vars, ac, av);
		vars.inpli = readline(vars.prompt);
		if (vars.inpli != NULL)
		{
			g_return_status = main2(&vars);
			if (vars.inpli[0] == '\0')
				continue ;
			g_return_status = main3(&vars);
		}
		else
			vars.looping = 0;
	}
	printf("exit\n");
	msh_free_envars(&vars);
	free(vars.prompt);
	return (g_return_status);
}
