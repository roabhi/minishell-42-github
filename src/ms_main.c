/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/27 20:54:35 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

//Global variable
int	g_return_status;

void	msh_sigint_handler(int sig)
{
	if (sig != 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "                              \n", 31);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_return_status = 1;
	}
}

void	msh_ignore_signals(t_vars *vars, int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac > 1 || av[1] != NULL)
	{
		ft_putendl_fd("ERROR: the program does not take any arguments!", 2);
		exit(1);
	}
	vars->sigbool = 1;
	signal(SIGINT, msh_sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	main2(t_vars *vars)
{
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
	if (vars->hdnumb > 0)
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

	vars.looping = 1;
	g_return_status = 0;
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
	msh_free_envars(&vars);
	free(vars.prompt);
	return (g_return_status);
}
